#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"

#ifdef linux
#include <semaphore.h>
#elif __APPLE__
#include "zemaphore.h"
#endif

typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;

sem_t privilege;

void rwlock_init(rwlock_t *lock) {
    lock->readers = 0;
    Sem_init(&lock->lock, 1);
    Sem_init(&lock->writelock, 1);
}

void rwlock_acquire_readlock(rwlock_t *lock) {
    Sem_wait(&privilege);
    Sem_wait(&lock->lock);
    lock->readers++;
    if (lock->readers == 1)
	     Sem_wait(&lock->writelock);
    Sem_post(&lock->lock);
    Sem_post(&privilege);
}

void rwlock_release_readlock(rwlock_t *lock) {
    Sem_wait(&lock->lock);
    lock->readers--;
    if (lock->readers == 0)
	     Sem_post(&lock->writelock);
    Sem_post(&lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    Sem_wait(&lock->writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    Sem_post(&lock->writelock);
}

int read_loops;
int write_loops;
int counter = 0;

rwlock_t mutex;

void *reader(void *arg) {
    int i;
    int local = 0;

    for (i = 0; i < read_loops; i++) {
    	rwlock_acquire_readlock(&mutex);
    	local = counter;
    	rwlock_release_readlock(&mutex);
    	printf("reader %d read %d\n",(int)arg, local);
    }
    printf("read done: %d\n", local);
    return NULL;
}

void *writer(void *arg) {
    int i;

    Sem_wait(&privilege);
    printf("start writing\n");
    for (i = 0; i < write_loops; i++) {
    	rwlock_acquire_writelock(&mutex);
    	counter++;
    	rwlock_release_writelock(&mutex);
    }
    printf("write done\n");
    Sem_post(&privilege);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
	fprintf(stderr, "usage: rwlock readloops writeloops readers\n");
	exit(1);
    }
    read_loops = atoi(argv[1]);
    write_loops = atoi(argv[2]);
    int readers = atoi(argv[3]);

    rwlock_init(&mutex);
    Sem_init(&privilege, 1);
    pthread_t c1;
    pthread_t thread[readers];

    Pthread_create(&c1, NULL, writer, NULL);
    for(int i =0; i < readers; i ++)
      Pthread_create(&thread[i], NULL, reader, (void*)(int)i);



    for(int i = 0; i < readers; i ++)
      Pthread_join(thread[i], NULL);

    Pthread_join(c1, NULL);
    printf("all done\n");
    return 0;
}
