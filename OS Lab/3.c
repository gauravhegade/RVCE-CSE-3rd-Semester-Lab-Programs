// Thread management using Pthread Library
// To demonstrate use of pthread library functions to create and manage threads,
// using a program that raises the numbers to the power of their corresponding
// row in the matrix (matrix indexed from 1). Implementation:

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int a[4][4], b[4][4];
void *matrixeval(void *val) {
  int *thno = (int *)val;
  for (int i = 0; i < 4; i++)
    b[(*thno)][i] = a[(*thno)][i];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < (*thno); j++)
      b[(*thno)][i] *= (a[(*thno)][i]);
}
int main() {
  pthread_t tid[4];
  int i, j;
  for (i = 0; i < 4; i++) {
    printf("Enter the elements of row %d: ", i + 1);
    for (j = 0; j < 4; j++)
      scanf("%d", &a[i][j]);
  }
  printf("Before processing:\n");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      printf("%d ", a[i][j]);
    printf("\n");
  }
  for (i = 0; i < 4; i++) {
    pthread_create(&tid[i], NULL, matrixeval, (void *)&i);
    sleep(1);
  }
  for (i = 0; i < 4; i++)
    pthread_join(tid[i], NULL);
  printf("After processing:\n");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      printf("%d ", b[i][j]);
    printf("\n");
  }
  pthread_exit(NULL);
  return 0;
}