#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#define SADDR struct sockaddr

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Too few arguments \n");
    printf("usage %s port \n", argv[0]);
    exit(1);
  }

  const size_t kSize = sizeof(struct sockaddr_in);
  int lfd, cfd;
  int nread;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  pid_t child_pid = 0;

  int pipeEnds[2];
  pipe(pipeEnds);

  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
//   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(atoi(argv[1]));
  setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void*)true, sizeof(int));

  if (bind(lfd, (SADDR *)&servaddr, kSize) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(lfd, 5) < 0) {
    perror("listen");
    exit(1);
  }
  while (1) {
    unsigned int clilen = kSize;

    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0) {
      perror("accept");
      exit(1);
    }
    printf("connection established\n");
    uint64_t num = 0;
    if (read(cfd, (void *)&num, sizeof(num)) == -1) {
      perror("read");
      exit(1);
    } else {
      child_pid = fork();
      if (child_pid >= 0) {
        /////////////////////////// UDP code ///////////
        close(pipeEnds[0]);

        int sockfd, n;
        int SERV_PORT = 49151;
        char ipadr[16];
        struct sockaddr_in servaddr1;
        struct sockaddr_in cliaddr;

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
          perror("socket problem");
          exit(1);
        }

        memset(&servaddr, 0, sizeof(struct sockaddr_in));
        servaddr1.sin_family = AF_INET;
        // servaddr1.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr1.sin_addr.s_addr = inet_addr("127.0.1.24");
        servaddr1.sin_port = htons(SERV_PORT);

        if (bind(sockfd, (SADDR *)&servaddr1, sizeof(struct sockaddr_in)) < 0) {
          perror("bind problem");
          exit(1);
        }
        printf("UDP-SERVER starts...\n");
        uint64_t msg = 0;

        while (1) {
          unsigned int len = sizeof(struct sockaddr_in);

          if ((n = recvfrom(sockfd, (void *)&msg, sizeof(msg), 0,
                            (SADDR *)&cliaddr, &len)) < 0) {
            perror("recvfrom");
            exit(1);
          }

          printf(
              "REQUEST %ull      FROM %s : %d\n", msg,
              inet_ntop(AF_INET, (void *)&cliaddr.sin_addr.s_addr, ipadr, 16),
              ntohs(cliaddr.sin_port));

          write(pipeEnds[1], &msg, sizeof(uint64_t));
        }
        /////////////////////////////////////////////////
      }
    }
    int checklist[num];
    int all = 0;
    for (uint64_t i = 0; i < num; i++)
      checklist[i] = 0;
    close(pipeEnds[1]);
    while (1) {
      all = 1;
      uint64_t i = 0;
      while (read(pipeEnds[0], &i, sizeof(uint64_t)) > 0) {
        if (i == 0)
          break;
        checklist[i - 1] = 1;
      }
      for (uint64_t j = 0; j < num; j++)
        if (checklist[j] == 0) {
            j ++;
          send(lfd, (void *)&j, sizeof(j), 0);
          all = 0;
          j--;
        }
      if (all == 1) {
        uint64_t k = 0;
        send(lfd, (void *)&k, sizeof(uint64_t), 0);
        kill(child_pid, SIGKILL);
        break;
      }
    }
  }

  close(cfd);
}
