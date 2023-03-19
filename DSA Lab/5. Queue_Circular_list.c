#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *addr;
};
typedef struct node *NODE;

NODE enqueue(NODE last,int item)
{
    NODE temp,cur;
    temp=(NODE)malloc(sizeof(struct node));
    temp->data=item;
    if(last==NULL)
    {
       temp->addr=temp;
       return temp;
    }
    else
    {
        temp->addr=last->addr;
        last->addr=temp;
        return temp;
    }
}

NODE dequeue(NODE last)
{
    NODE temp;
    if(last==NULL)
    {
        printf("\n List is empty");
        return NULL;
    }
    if(last->addr==last)
    {
        printf("\n Node deleted is %d\n",last->data);
        free(last);
        last=NULL;
        return NULL;
    }
    temp=last->addr;
    printf("\n Node deleted is %d\n",temp->data);
    last->addr=temp->addr;
    free(temp);
    return last;
}

void display(NODE last)
{
    NODE temp;
    if(last==NULL)
        printf("\n Queue is empty");
    else
    {
        printf("\n Queue content are\n");
        temp=last->addr;
        while(temp!=last)
        {
            printf("%d\t",temp->data);
            temp=temp->addr;
        }
        printf("%d\t",temp->data);
    }
}

int main()
{
    NODE last=NULL;
    int ch,item;
    for(;;)
    {
        printf("\n 1. Enqueue");
        printf("\n 2. Dequeue");
        printf("\n 3. Display");
        printf("\n 4. Exit");
        printf("\n Read Choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("\n Read data to be inserted:");
                   scanf("%d",&item);
                   last=enqueue(last,item);
                   break;
            case 2:last=dequeue(last);
                   break;
            case 3:display(last);
                   break;
            default:exit(0);
        }
    }
    return 0;
}
