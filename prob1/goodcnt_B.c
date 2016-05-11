#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NITER 1000000
#define THREADS 4

key_t key;
int shmid;
int *cnt;

enum {STATE1, STATE2, STATE3, STATE4} state = STATE1;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond4 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t count_sem;

void *Count1(void *a)
{
	unsigned int i, *myid;
	myid = (unsigned int *) a;

	for(i = 0; i < NITER; i++) {
		pthread_mutex_lock(&mutex);
		while(state != STATE1)
			pthread_cond_wait(&cond1, &mutex);
		pthread_mutex_unlock(&mutex);

		sem_wait(&count_sem);
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
	//printf("Thread %d segment contains: \"%d\"\n", *myid, *cnt);
		sem_post(&count_sem);

		pthread_mutex_lock(&mutex);
		state = STATE2;
		pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&mutex);
	}
}

void *Count2(void *a)
{
	unsigned int i, *myid;
	myid = (unsigned int *) a;

	for(i = 0; i < NITER; i++) {
		pthread_mutex_lock(&mutex);
		while(state != STATE2)
			pthread_cond_wait(&cond2, &mutex);
		pthread_mutex_unlock(&mutex);

		sem_wait(&count_sem);
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
	//printf("Thread %d segment contains: \"%d\"\n", *myid, *cnt);
		sem_post(&count_sem);

		pthread_mutex_lock(&mutex);
		state = STATE3;
		pthread_cond_signal(&cond3);
		pthread_mutex_unlock(&mutex);
	}
}

void *Count3(void *a)
{
	unsigned int i, *myid;
	myid = (unsigned int *) a;

	for(i = 0; i < NITER; i++) {
		pthread_mutex_lock(&mutex);
		while(state != STATE3)
			pthread_cond_wait(&cond3, &mutex);
		pthread_mutex_unlock(&mutex);

		sem_wait(&count_sem);
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
	//printf("Thread %d segment contains: \"%d\"\n", *myid, *cnt);
		sem_post(&count_sem);

		pthread_mutex_lock(&mutex);
		state = STATE4;
		pthread_cond_signal(&cond4);
		pthread_mutex_unlock(&mutex);
	}
}

void *Count4(void *a)
{
	unsigned int i, *myid;
	myid = (unsigned int *) a;

	for(i = 0; i < NITER; i++) {
		pthread_mutex_lock(&mutex);
		while(state != STATE4)
			pthread_cond_wait(&cond4, &mutex);
		pthread_mutex_unlock(&mutex);

		sem_wait(&count_sem);
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
		*cnt = *cnt + 1;
	//printf("Thread %d segment contains: \"%d\"\n", *myid, *cnt);
		sem_post(&count_sem);

		pthread_mutex_lock(&mutex);
		state = STATE1;
		pthread_cond_signal(&cond1);
		pthread_mutex_unlock(&mutex);
	}
}

void sharedMemory()
{

    // make the key:
    if ((key = ftok("file", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    // connect to (and possibly create) the segment:
    if ((shmid = shmget(key, sizeof(pthread_t), 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // attach to the segment to get a pointer to it:
    cnt = shmat(shmid, (void *)0, 0);
    if (cnt == (int *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // read or modify the segment, based on the command line:
	*cnt = 0;
    printf("segment contains: \"%d\"\n", *cnt);

}

void dtachMemory() {
    // detach from the segment:
    if (shmdt(cnt) == -1) {
        perror("shmdt");
        exit(1);
    }
}


int main(int argc, char * argv[])
{
    pthread_t tid[THREADS];

	sharedMemory();

	int res = sem_init(&count_sem, 0, 1); // 0 is locked
	if(res < 0) {
		perror("Semaphore initialization failed");
		exit(0);
	}

	unsigned int i, id[THREADS];

	for(i = 0; i < THREADS; i++) {
		id[i] = i+1;
//		pthread_create(&tid[i], NULL, Count1, (void* ) &id[i]);
	}
	pthread_create(&tid[0], NULL, Count1, (void* ) &id[0]);
	pthread_create(&tid[1], NULL, Count2, (void* ) &id[1]);
	pthread_create(&tid[2], NULL, Count3, (void* ) &id[2]);
	pthread_create(&tid[3], NULL, Count4, (void* ) &id[3]);

	for(i = 0; i < THREADS; i++) {
		pthread_join(tid[i], NULL);	// wait for the thread i to finish
	}

    if (*cnt != 5*THREADS*NITER)
        printf("\n BOOM! cnt is [%d], should be %d\n", *cnt, 5*THREADS*NITER);
    else
        printf("\n OK! cnt is [%d]\n", *cnt);

	sem_destroy(&count_sem);
	dtachMemory();
	pthread_exit(NULL);
}

