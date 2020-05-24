#include "factorial.h"
#include "pthread.h"
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
struct Server {
  char ip[255];
  int port;
};

int main(int argc, char **argv) {
  uint64_t k = -1;
  uint64_t mod = -1;
  double elapsed_time;
  char servers[255] = {
      '\0'}; // TODO: explain why 255 (is maximal length of path)

  
  // TODO: for one server here, rewrite with servers from file *looks like done*
  unsigned int servers_num = 1;
  struct Server *to = malloc(sizeof(struct Server) * 1);
  struct timeval finish_time;
   to[0].port = 20001;
   memcpy(to[0].ip, "95.72.133.152", sizeof("95.72.133.152"));

  // TODO: work continiously, rewrite to make parallel
  int ars = k / servers_num;
  int left = k % servers_num;
  int sck[servers_num];
  pthread_t threads[servers_num];
    struct timeval start_time;

    struct hostent *hostname = gethostbyname(to[0].ip);
    if (hostname == NULL) {
      fprintf(stderr, "gethostbyname failed with %s\n", to[0].ip);
      exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(to[0].port);
    server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr_list[0]);

    sck[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0) {
      fprintf(stderr, "Socket creation failed!\n");
      exit(1);
    }

    if (connect(sck[0], (struct sockaddr *)&server, sizeof(server)) < 0) {
      fprintf(stderr, "Connection failed\n");
      exit(1);
    }

    char task[sizeof(int)];
    int a = 12;
    memcpy(task, &a, sizeof(int));

    gettimeofday(&start_time, NULL);
    
    if (send(sck[0], task, sizeof(task), 0) < 0) {
      fprintf(stderr, "Send failed\n");
      exit(1);
    }
    char response[sizeof(int)];
    recv(sck[0], response, sizeof(response), 0);
    gettimeofday(&finish_time, NULL);

  elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  printf("time = %f\n", elapsed_time);
  return 0;
}