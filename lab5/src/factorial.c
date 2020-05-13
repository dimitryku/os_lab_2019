#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

struct FactArgs{
    int begin;
    int end;
};
int factor = 1;
int modd = 0;
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

void CountPart(void *args) {
  struct FactArgs *arrs = (struct FactArgs *)args;
  for(int i = arrs->begin; i < arrs->end; i++)
    {
        int num = i%modd;
        pthread_mutex_lock(&mutx);
        factor = factor%modd * num;
        pthread_mutex_unlock(&mutx);
    }
}


int main(int argc, char **argv)
{
    int pnum = 0;
    int k = getopt(argc,argv, "k:");
    if (k <= 0)
    {
        printf("needs -k and it is positive number");
        return 1;
    }

    while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"mod", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            modd = atoi(optarg);
            if (modd <= 0) {
                printf("mod is a positive number\n");
                return 1;
            }
            break;
          case 1:
            pnum = atoi(optarg);
            if (pnum <= 0) {
                printf("pnum is a positive number\n");
                return 1;
            }
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (modd == 0 || pnum == 0) {
    printf("Usage: %s -k \"num\" --mod \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int ars = k/pnum;
  int left = k%pnum;
  struct FactArgs args[pnum];
  for(int i = 0; i < pnum; i++)
  {
      args[i].begin = ars*i + (left < i ? left : i);
      printf("%d\n", args[i].begin);
      args[i].end = ars*(i+1) + (left < i+1 ? left : i+1);
      printf("%d\n", args[i].end);
  }







    return 0;
}