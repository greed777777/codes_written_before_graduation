#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include "common.h"
#include "common_threads.h"

#ifdef linux
#include <semaphore.h>
#elif __APPLE__
#include "zemaphore.h"
#endif

int max;
int loops;
int quota;
int leaveWorker = 0;
int *buffer;

int use  = 0;
int fill = 0;

sem_t empty;
sem_t full;
sem_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#define CMAX (10)
#define PMAX (10)
int consumers = 1;
int producers = 1;

int do_fill(int value) {
    buffer[fill] = value;
    fill++;
    if (fill == max)
	     fill = 0;
    return value;
}

int do_get() {
    int tmp = buffer[use];
    use++;
    if (use == max)
      use = 0;
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < quota; i++) {
    	Sem_wait(&empty);
    	Sem_wait(&mutex);
      printf("producer %lld: %d\n", (long long int) arg, do_fill(i+(long long int) arg*quota));
    	Sem_post(&mutex);
    	Sem_post(&full);
    }
      pthread_mutex_lock(&lock);
      leaveWorker++;
      // printf("producer %lld: leave work\n", (long long int) arg);
      pthread_mutex_unlock(&lock);
    // end case
    if(leaveWorker == producers)
      for (i = 0; i < consumers; i++) {
        Sem_wait(&empty);
        Sem_wait(&mutex);
        printf("producer %lld: %d\n", (long long int) arg, do_fill(-1));
        Sem_post(&mutex);
        Sem_post(&full);
      }

    return NULL;
}

void *consumer(void *arg) {
    int tmp = 0;
    while (tmp != -1) {
    	Sem_wait(&full);
    	Sem_wait(&mutex);
    	tmp = do_get();
    	Sem_post(&mutex);
    	Sem_post(&empty);
      if(tmp == -1)
        // printf("consumer %lld: done\n", (long long int) arg);
        ;
      else
        printf("consumer %lld: %d\n", (long long int) arg, tmp);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
	fprintf(stderr, "usage: %s <buffersize> <loops> <producers> <consumers>\n", argv[0]);
	exit(1);
    }
    max   = atoi(argv[1]);
    loops = atoi(argv[2]);
    producers = atoi(argv[3]);
    consumers = atoi(argv[4]);

    quota = loops/producers;
    assert(consumers <= CMAX);
    assert(producers <= PMAX);

    buffer = (int *) malloc(max * sizeof(int));
    assert(buffer != NULL);
    int i;
    for (i = 0; i < max; i++) {
      buffer[i] = 0;
    }

    Sem_init(&empty, max); // max are empty
    Sem_init(&full, 0);    // 0 are full
    Sem_init(&mutex, 1);   // mutex

    pthread_t pid[PMAX], cid[CMAX];
    for (i = 0; i < producers; i++) {
      Pthread_create(&pid[i], NULL, producer, (void *) (long long int) i);
    }
    for (i = 0; i < consumers; i++) {
      Pthread_create(&cid[i], NULL, consumer, (void *) (long long int) i);
    }
    for (i = 0; i < producers; i++) {
      Pthread_join(pid[i], NULL);
    }

    for (i = 0; i < consumers; i++) {
      Pthread_join(cid[i], NULL);
    }
    return 0;
}
