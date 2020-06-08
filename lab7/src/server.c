#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
  setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)true, sizeof(int));

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
    int num = 0;
    if (read(cfd, &num, sizeof(int)) <= 0) {
      perror("read");
      exit(1);
    }
    // nice
    int SERV_PORT = 49001;
    if (write(cfd, &SERV_PORT, sizeof(int)) < 0) {
      perror("write");
      exit(1);
    }
    child_pid = fork();
    if (child_pid == 0) {
      /////////////////////////// UDP code //////////////////
      int sockfd, n;

      char ipadr[16];
      struct sockaddr_in servaddr1;
      struct sockaddr_in cliaddr;

      if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket problem");
        exit(1);
      }

      memset(&servaddr, 0, sizeof(struct sockaddr_in));
      servaddr1.sin_family = AF_INET;
      servaddr1.sin_addr.s_addr = inet_addr("127.0.1.24");
      servaddr1.sin_port = htons(SERV_PORT);

      if (bind(sockfd, (SADDR *)&servaddr1, sizeof(struct sockaddr_in)) < 0) {
        perror("bind problem");
        exit(1);
      }
      printf("UDP-SERVER starts...\n");
      int msg = 0;

      while (true) {
        unsigned int len = sizeof(struct sockaddr_in);
        printf("bb %d\n", msg);
        if ((n = recvfrom(sockfd, &msg, sizeof(msg), 0, (SADDR *)&cliaddr,
                          &len)) < 0) {
          perror("recvfrom");
          exit(1);
        }
        if (msg != 0) {
          printf("REQUEST %u      FROM %s : %d\n", msg,
                 inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ipadr, 16),
                 ntohs(cliaddr.sin_port));
        }

        write(pipeEnds[1], &msg, sizeof(int));
      }
      /////////////////////////////////////////////////
    }
    int checklist[num];
    int all = 0;
    for (int i = 0; i < num; i++)
      checklist[i] = 0;
      sleep(1);

    while (all != 1) {
      all = 1;
      int i = 0;
      while (read(pipeEnds[0], &i, sizeof(int)) > 0) {
        if (i == 0)
          break;
        checklist[i - 1] = 1;
      }
      for (int j = 0; j < num; j++)
        if (checklist[j] == 0) {
          j++;
          if (write(cfd, &j, sizeof(j)) < 0) {
            perror("write problem");
            exit(1);
          }
          all = 0;
          j--;
        }
    //   int j = 0;
    //   if (write(cfd, &j, sizeof(j)) < 0) {
    //     perror("write problem");
    //     exit(1);
    //   }

      if (all == 1) {
        int k = 0;
        write(cfd, (void *)&k, sizeof(int));
        kill(child_pid, SIGKILL);
        break;
      }
    }
  }

  close(cfd);
}


