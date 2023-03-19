// Process/Thread synchronization
// Application to demonstrate process/thread synchronization using semaphores
// and mutex. Implement either Dining philosophers problem, reader-writer or
// producer-consumer.

// Reader Writer:
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0, rcount = 0;
sem_t mutex, wr;
void *writer(void *p) {
  int *i = (int *)p;
  sem_wait(&wr);
  printf("\nWriter %d writes page number %d", *i, ++count);
  sem_post(&wr);
}
void *reader(void *p) {
  int *i = (int *)p;
  sem_wait(&mutex);
  rcount++;
  if (rcount == 1)
    sem_wait(&wr);
  sem_post(&mutex);
  printf("\nReader %d reads page number %d ", *i, count);
  sem_wait(&mutex);
  rcount--;
  if (rcount == 0)
    sem_post(&wr);
  sem_post(&mutex);
}
int main() {
  sem_init(&mutex, 0, 1);
  sem_init(&wr, 0, 1);
  int a[6] = {1, 2, 3, 1, 2, 3};
  pthread_t p[6];
  for (int i = 0; i < 3; i++)
    pthread_create(&p[i], NULL, writer, &a[i]);
  for (int i = 3; i < 6; i++)
    pthread_create(&p[i], NULL, reader, &a[i]);
  for (int i = 0; i < 6; i++)
    pthread_join(p[i], NULL);
}

// Producer consumer:
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define buffersize 10
pthread_mutex_t mutex;
pthread_t tidP[20], tidC[20];
sem_t full, empty;
int counter;
int buffer[buffersize];
void initialize() {
  pthread_mutex_init(&mutex, NULL);
  sem_init(&full, 1, 0);
  sem_init(&empty, 1, buffersize);
  counter = 0;
}
void write(int item) { buffer[counter++] = item; }
int read() { return (buffer[--counter]); }
void *producer(void *param) {
  int waittime, item, i;
  item = rand() % 5;
  waittime = rand() % 5;
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  printf("\nProducer has produced item: %d\n", item);
  write(item);
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
}
void *consumer(void *param) {
  int waittime, item;
  waittime = rand() % 5;
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  item = read();
  printf("\nConsumer has consumed item: %d\n", item);
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
}
int main() {
  int n1, n2, i;
  initialize();
  printf("\nEnter the no of producers: ");
  scanf("%d", &n1);
  printf("\nEnter the no of consumers: ");
  scanf("%d", &n2);
  for (i = 0; i < n1; i++)
    pthread_create(&tidP[i], NULL, producer, NULL);
  for (i = 0; i < n2; i++)
    pthread_create(&tidC[i], NULL, consumer, NULL);
  for (i = 0; i < n1; i++)
    pthread_join(tidP[i], NULL);
  for (i = 0; i < n2; i++)
    pthread_join(tidC[i], NULL);
  // sleep(5);
  exit(0);
}

// Dining Philosopher’s Problem :
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N
int state[N];
int phil[N] = {0, 1, 2, 3, 4};
sem_t mutex;
sem_t S[N];
void test(int phnum) {
  if (state[phnum] == HUNGRY && state[LEFT] != EATING &&
      state[RIGHT] != EATING) {
    // state that eating
    state[phnum] = EATING;
    sleep(2);
    printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1,
           phnum + 1);
    printf("Philosopher %d is Eating\n", phnum + 1);
    // sem_post(&S[phnum]) has no effect
    // during takefork
    // used to wake up hungry philosophers
    // during putfork
    sem_post(&S[phnum]);
  }
}
// take up chopsticks
void take_fork(int phnum) {
  sem_wait(&mutex);
  // state that hungry
  state[phnum] = HUNGRY;
  printf("Philosopher %d is Hungry\n", phnum + 1);
  // eat if neighbours are not eating
  test(phnum);
  sem_post(&mutex);
  // if unable to eat wait to be signalled
  sem_wait(&S[phnum]);
  sleep(1);
}
// put down chopsticks
void put_fork(int phnum) {
  sem_wait(&mutex);
  // state that thinking
  state[phnum] = THINKING;
  printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1,
         phnum + 1);
  printf("Philosopher %d is thinking\n", phnum + 1);
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}
void *philospher(void *num) {
  while (1) {
    int *i = num;
    sleep(1);
    take_fork(*i);
    sleep(0);
    put_fork(*i);
  }
}
int main() {
  int i;
  pthread_t thread_id[N];
  // initialize the semaphores
  sem_init(&mutex, 0, 1);
  for (i = 0; i < N; i++)
    sem_init(&S[i], 0, 0);
  for (i = 0; i < N; i++) {
    // create philosopher processes
    pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
    printf("Philosopher %d is thinking\n", i + 1);
  }
  for (i = 0; i < N; i++)
    pthread_join(thread_id[i], NULL);
}
