#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    int i = 0;
    for(; i < 5; i++){
        pid_t child_pid = fork();
        if(child_pid >= 0)
            {
            if (child_pid == 0)
                {
                    return 0;
                }
            }
    }
    sleep(60);
    return 0;
}