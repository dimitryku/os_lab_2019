#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
void GenerateArray(int *array, unsigned int array_size, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < array_size; i++) {
    array[i] = rand();
  }
}

void WakeUpAndKillYorChildren ()
{
    int a = 0;
    kill(-1, SIGKILL);
    while(waitpid(-1, &a, WNOHANG)!=0);
}
