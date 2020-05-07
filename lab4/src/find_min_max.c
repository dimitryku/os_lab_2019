#include "find_min_max.h"
#include "stdio.h"
#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  //unable to use wait() becouse of conflicts with alarm()
  {int a;
  for(int i = 0; i < 100000; i++)
  for(int j = 0; j < 2000; j++)
   a = i;}

  for(int i = begin; i < end; i++)
  {
    if (array[i] > min_max.max)
        min_max.max = array[i];
    if (array[i] < min_max.min)
        min_max.min = array[i];
  }

  return min_max;
}
