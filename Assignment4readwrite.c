/*
use the pthread flag with gcc to compile this code
~$ gcc -pthread Ass4readwrite.c 
*/

// Reader-Writer problem using mutex
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// no. of readers
    int rcnt=0;
 
    // no. of writers
    int wcnt=0;
 
    // no. of readers waiting
    int waitr=0;
 
    // no. of writers waiting
    int waitw=0;
 
    // condition variable to check whether reader can read
    pthread_cond_t canread;
 
    // condition variable to check whether writer can write
    pthread_cond_t canwrite;
 
    // mutex for synchronization
    pthread_mutex_t condlock;
 
    pthread_t r[5], w[5];

    int id[5];
// mutex provide synchronization so that no other thread
// can change the value of data
void beginread(int i)
{
        pthread_mutex_lock(&condlock);
 
        // if there are active or waiting writers
        if (wcnt == 1 || waitw > 0) {
            // incrementing waiting readers
            waitr++;
 
            // reader suspended
            pthread_cond_wait(&canread, &condlock);
            waitr--;
        }
 
        // else reader reads the resource
        rcnt++;
        printf("reader %d is reading\n", i);
        pthread_mutex_unlock(&condlock);
        pthread_cond_broadcast(&canread);
}
 
void endread(int i)
{
 
        // if there are no readers left then writer enters monitor
        pthread_mutex_lock(&condlock);
 
        if (--rcnt == 0)
            pthread_cond_signal(&canwrite);
 
        pthread_mutex_unlock(&condlock);
}
 
void beginwrite(int i)
{
        pthread_mutex_lock(&condlock);
 
        // a writer can enter when there are no active
        // or waiting readers or other writer
        if (wcnt == 1 || rcnt > 0) {
            ++waitw;
            pthread_cond_wait(&canwrite, &condlock);
            --waitw;
        }
        wcnt = 1;
        printf("writer %d is writing\n", i);
        pthread_mutex_unlock(&condlock);
}
 
void endwrite(int i)
{
        pthread_mutex_lock(&condlock);
        wcnt = 0;
 
        // if any readers are waiting, threads are unblocked
        if (waitr > 0)
            pthread_cond_signal(&canread);
        else
            pthread_cond_signal(&canwrite);
        pthread_mutex_unlock(&condlock);
}

void *reader(void* id)
{
    int c = 0;
    int i = *(int*)id;
 
    // each reader attempts to read 5 times
    while (c < 5) {
        usleep(1);
        beginread(i);
        endread(i);
        c++;
    }
}
 
void *writer(void* id)
{
    int c = 0;
    int i = *(int*)id;
 
    // each writer attempts to write 5 times
    while (c < 5) {
        usleep(1);
        beginwrite(i);
        endwrite(i);
        c++;
    }
}
 

int main()
{
    pthread_cond_init(&canread, NULL);
    pthread_cond_init(&canwrite, NULL);
    pthread_mutex_init(&condlock, NULL);

    for (int i = 0; i < 5; i++) {
        id[i] = i;
 
        // creating threads which execute reader function
        pthread_create(&r[i], NULL, &reader, &id[i]);
 
        // creating threads which execute writer function
        pthread_create(&w[i], NULL, &writer, &id[i]);
    }
 
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(w[i], NULL);
    }
}
    


