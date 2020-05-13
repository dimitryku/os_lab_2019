#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


pthread_mutex_t mutx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutx2 = PTHREAD_MUTEX_INITIALIZER;
int first_num = 0;
int second_num = 0;

void first_task()
{
    printf("1) trying to read first_num\n");
    pthread_mutex_lock(&mutx1);
    first_num++;
    printf("1) first_num is locked, updated and now = %d\n", first_num);
    printf("1) trying to reach second_num\n");
    pthread_mutex_lock(&mutx2);
    second_num++;
    printf("1) second_num is locked, updated and now = %d\n", second_num);
    pthread_mutex_unlock(&mutx1);
    pthread_mutex_unlock(&mutx2);
}

void second_task()
{
    printf("2) trying to read second_num\n");
    pthread_mutex_lock(&mutx2);
    second_num+=2;
    printf("2) second_num is locked, updated and now = %d\n", second_num);
    printf("2) trying to reach first_num\n");
    pthread_mutex_lock(&mutx1);
    first_num+=2;
    printf("2) first_num is locked, updated and now = %d\n", first_num);
    pthread_mutex_unlock(&mutx2);
    pthread_mutex_unlock(&mutx1);
}


int main()
{
    pthread_t threads[2];
    if(pthread_create(&threads[0], NULL, (void*)first_task, NULL)!=0)
    {
        printf("thread creation error\n");
        return 1;
    }
    if(pthread_create(&threads[1], NULL, (void*)second_task, NULL) !=0)
    {
        printf("thread creation error\n");
        return 1;
    }
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    printf("program finished successfully\n");


    return 0;
}