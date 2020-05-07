#include "find_min_max.h"
#include "stdio.h"
#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;
  printf("loader\n");
  int a;
  for(int i = 0; i < 100000; i++)
  for(int j = 0; j < 100000; j++)
  //for(int k = 0; k < 100000; k++)
  //for(int l = 0; l < 100000; l++)
   a = i;

  for(int i = begin; i < end; i++)
  {
    if (array[i] > min_max.max)
        min_max.max = array[i];
    if (array[i] < min_max.min)
        min_max.min = array[i];
  }

  return min_max;
}
