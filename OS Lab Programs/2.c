// Process control system calls
// Application to demonstrate use of fork, execve, wait, getpid, exit system
// calls. A Host Program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
  printf("Main Function: \n");
  int retval = 1;
  pid_t pid = fork();
  if (pid < 0) {
    printf("Error in fork operation\n");
  }
  if (pid == 0) {
    printf("PID for Child process: %d\nPID of its parent process: %d\n",
           getpid(), getppid());
    execl("./binsearch", argv[1], NULL);
  } else {
    printf("PID of parent process: %d\n", getpid());
    wait(&retval);
    if (WIFEXITED(retval) == 1) {
      printf("Child terminated normally\n");
    } else {
      printf("Child terminated abnormally\n");
      exit(0);
    }
  }
  return 0;
}

// Binary search application
#include <stdio.h>
int binarySearch(int arr[], int l, int r, int x) {
  if (r >= l) {
    int mid = l + (r - l) / 2;
    if (arr[mid] == x)
      return 1;
    if (arr[mid] > x)
      return binarySearch(arr, l, mid - 1, x);
    return binarySearch(arr, mid + 1, r, x);
  }
  return -1;
}
void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
void sort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
}
int main(void) {
  int n, key, arr[10];
  printf("Enter the number of elements in the array: ");
  scanf("%d", &n);
  printf("Enter the elements: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);
  sort(arr, n);
  printf("Enter element to be searched: ");
  scanf("%d", &key);
  int result = binarySearch(arr, 0, n - 1, key);
  if (result == -1)
    printf("Element is not present in array");
  else
    printf("Element is present");
  return 0;
}