#include <arpa/inet.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd;
  int nread;
  uint64_t num = atoi(argv[3]);
  int size = 0;
  struct sockaddr_in servaddr;

  if (argc < 4) {
    printf("Too few arguments \n");
    printf("usage %s ip port num\n", argv[0]);
    exit(1);
  }

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creating");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    perror("bad address");
    exit(1);
  }
  
  servaddr.sin_port = htons(atoi(argv[2]));

  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }

  if (write(fd, (void *)&num, sizeof(int64_t)) < 0) {
    perror("write");
    exit(1);
  }
  uint64_t response = 0;
  if (recv(fd, (void *)&response, sizeof(response), 0) < 0) {
    fprintf(stderr, "Recieve failed\n");
    exit(1);
  }
  sleep(1);
  ////////////////////////////////////////////
  printf("udp part of client \n");
  int SERV_PORT = response;
  int sockfd, n;
  struct sockaddr_in servaddr1;
  struct sockaddr_in cliaddr;

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);

  if (inet_pton(AF_INET, "127.0.1.24", &servaddr.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }
  for (uint64_t i = 1; i < num; i++) {
    if (sendto(sockfd, (void *)&i, sizeof(i), 0, (SADDR *)&servaddr,
               sizeof(servaddr)) == -1) {
      perror("sendto problem");
      exit(1);
    }
  }
  uint64_t i = 0;
  if (sendto(sockfd, (void *)&i, sizeof(i), 0, (SADDR *)&servaddr,
               sizeof(servaddr)) == -1) {
      perror("sendto problem");
      exit(1);
    }
    sleep(1);
  ////////////////////////////////////
  while (true) {
    response = 0;
    if (recv(fd, (void *)&response, sizeof(response), 0) < 0) {
      fprintf(stderr, "Recieve failed\n");
      exit(1);
    }

    if (response != 0) {
      if (sendto(sockfd, (void *)&response, sizeof(response), 0,
                 (SADDR *)&servaddr, sizeof(servaddr)) == -1) {
        perror("sendto problem");
        exit(1);
      }
      response = 0;
      if (sendto(sockfd, (void *)&response, sizeof(response), 0,
                 (SADDR *)&servaddr, sizeof(servaddr)) == -1) {
        perror("sendto problem");
        exit(1);
      }
    } else {
      break;
    }
  }

  close(sockfd);
  close(fd);
  exit(0);
}
