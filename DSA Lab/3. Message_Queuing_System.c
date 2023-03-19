#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define SIZE 5

struct queue
{
int r;
int f;
char data[SIZE][15];
};
typedef struct queue QUEUE;

void Enqueue(QUEUE *q,char item[15])
{
    if(q->f == (q->r+1)%SIZE)
        printf("\n Circular Queue is full");
    else
    {
        q->r= (q->r+1) % SIZE;
        strcpy(q->data[q->r],item);
        if(q->f == -1)
            q->f=0;
    }
}

char *Dequeue(QUEUE *q)
{
    char *d;
    if(q->f==-1)
    {
        printf("\n Circular Queue empty");
        return NULL;
    }
    else
    {
        d=q->data[q->f];
        if(q->f == q->r)
        {
            q->f=-1;
            q->r=-1;
        }
        else
            q->f= (q->f+1)%SIZE;
        return d;
    }
}

void display(QUEUE q)
{
    int i;
    if(q.f==-1)
        printf("\n Circular queue Empty");
    else
    {
        printf("\n Circular queue Content are\n");
        for(i=q.f;i!=q.r;i=(i+1)%SIZE)
            printf("%s\n",q.data[i]);
        printf("%s\n",q.data[i]);
    }
}

int main()
{
    int ch;
    char item[15];
    char *d;
    QUEUE q;
    q.f=-1;
    q.r=-1;
    for(;;)
    {
        printf("\n 1. Insert");
        printf("\n 2. Delete");
        printf("\n 3. Display");
        printf("\n 4. Exit");
        printf("\n Read Choice:");
        scanf("%d",&ch);
        getchar();
        switch(ch)
        {
            case 1:printf("\n Read message to be inserted :");
            gets(item);
            Enqueue(&q,item);
            break;
            case 2:d=Dequeue(&q);
            if(d!=NULL)
                printf("\n Message deleted is %s\n",d);
            break;
            case 3:display(q);
            break;
            default:exit(0);
        }
    }
    return 0;
}

