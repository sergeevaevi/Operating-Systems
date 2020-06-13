#include <stdio.h>

#include "mythreads.h"

int balance = 0;
//pthread_mutex_t mutex;
void* worker(void* arg) {
//    pthread_mutex_lock(&mutex);
    balance++; // unprotected access
//    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
//    pthread_mutex_init(&mutex, NULL);
    Pthread_create(&p, NULL, worker, NULL);
//    pthread_mutex_lock(&mutex);
    balance++; // unprotected access
//    pthread_mutex_unlock(&mutex);
//    pthread_mutex_destroy(&mutex);
    Pthread_join(p, NULL);
    return 0;
}
