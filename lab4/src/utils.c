#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void GenerateArray(int *array, unsigned int array_size, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < array_size; i++) {
    array[i] = rand();
  }
}

void WakeUpAndKillYorChildren(int signo)
{
    int a;
    kill(0, SIGKILL);
    while(waitpid(0, &a, WNOHANG)> 0);
    return;
}
