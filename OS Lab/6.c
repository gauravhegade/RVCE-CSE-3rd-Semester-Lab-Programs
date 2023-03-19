// Memory Management
// Write a program to simulate Buddy memory allocation algorithm.
// BUDDY SYSTEM CODE

#include <stdio.h>
#include <stdlib.h>
int tree[2050], i, j, k;
void segmentalloc(int, int);
void makedivided(int);
void makefree(int);
void printing(int, int);
int place(int);
int power(int, int);
int main() {
  int totsize, req, ch;
  printf("\nBuddy System Requirements : ");
  printf("\nE\nnter total size of memory: ");
  scanf("%d", &totsize);
  for (;;) {
    printf("\n1. Allocate process into memory\n2.Remove process from "
           "memory\n3.Tree structure for memory allocation map\n4.exit\nEnter "
           "choice : ");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      printf("\nMemory Allocation : ");
      printf("\nEnter size of process : ");
      scanf("%d", &req);
      segmentalloc(totsize, req);
      break;
    case 2:
      printf("\nMemory Deallocation : ");
      printf("\nEnter size of process to be removed : ");
      scanf("%d", &req);
      makefree(req);
      break;
    case 3:
      printf("\nMemory Allocation Map : ");
      printing(totsize, 0);
      break;
    default:
      exit(0);
    }
  }
}
void segmentalloc(int total, int req) {
  int size = total, flevel = 0;
  if (req > size) {
    printf("\nSystem does not have enough memory ! ");
    return;
  }
  while (1) {
    if (req < size && req > size / 2)
      break;
    else {
      size = size / 2;
      flevel++;
    }
  }
  for (int i = power(2, flevel) - 1; i <= power(2, flevel + 1) - 2; i++) {
    if (tree[i] == 0 && place(i)) {
      tree[i] = req;
      makedivided(i);
      printf("\nSuccessful allocation ! ");
      break;
    }
    if (i == power(2, flevel + 1) - 1) {
      printf("\nDoes not have enough memory !");
    }
  }
}
void makedivided(int node) {
  while (node != 0) {
    node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
    tree[node] = 1;
  }
}
int place(int node) {
  while (node != 0) {
    node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
    if (tree[node] > 1)
      return 0;
  }
  return 1;
}
void makefree(int req) {
  int node = 0;
  while (1) {
    if (tree[node] == req)
      break;
    else
      node++;
  }
  tree[node] = 0;
  while (node != 0) {
    // node=(node%2==0)?(node-1)/2:node/2;
    if (tree[node] == 0 && tree[(node % 2 == 0) ? (node - 1) : node + 1] == 0) {
      tree[(node % 2 == 0) ? (node - 1) / 2 : node / 2] = 0;
      node = (node % 2 == 0) ? (node - 1) / 2 : node / 2;
    } else
      break;
  }
}
int power(int x, int y) {
  int ans = 1;
  for (int i = 0; i < y; i++)
    ans *= x;
  return ans;
}
void printing(int tot, int node) {
  int perm = 0, llimit, ulimit, tab;
  if (node == 0)
    perm = 1;
  else if (node % 2 == 0)
    perm = tree[(node - 1) / 2] == 1 ? 1 : 0;
  else
    perm = tree[node / 2] == 1 ? 1 : 0;
  if (perm) {
    llimit = ulimit = tab = 0;
    while (1) {
      if (node >= llimit && node <= ulimit)
        break;
      else {
        tab++;
        printf(" ");
        llimit = ulimit + 1;
        ulimit = 2 * ulimit + 2;
      }
    }
    printf("%d", tot / power(2, tab));
    if (tree[node] > 1)
      printf(" --> Allocates %d ", tree[node]);
    else if (tree[node] == 1)
      printf(" --> Divided");
    else
      printf(" --> Free");
    printing(tot, 2 * node + 1);
    printing(tot, 2 * node + 2);
  }
}