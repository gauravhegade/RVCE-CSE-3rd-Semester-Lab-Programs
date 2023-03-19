#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *addr;
};
typedef struct node *NODE;

NODE insertbegin(NODE head,int item)
{
    NODE temp,cur;
    temp=(NODE)malloc(sizeof(struct node));
    temp->data=item;
    temp->addr=NULL;
    if(head->addr == NULL)
    {
        head->addr=temp;
        return head;
    }
    temp->addr=head->addr;
    head->addr=temp;
    return head;
}

NODE insertend(NODE head,int item)
{
    NODE temp,cur;
    temp=(NODE)malloc(sizeof(struct node));
    temp->data=item;
    temp->addr=NULL;
    if(head->addr == NULL)
    {
        head->addr=temp;
        return head;
    }
    cur=head->addr;
    while(cur->addr!=NULL)
        cur = cur->addr;
    cur->addr=temp;
    return head;
}

void appendzero(NODE head1,NODE head2)
{
    int ct1=1,ct2=1,i;
    NODE temp;
    temp=head1->addr;
    while(temp!=NULL)
    {
        temp=temp->addr;
        ct1 = ct1 + 1;
    }
    temp=head2->addr;
    while(temp!=NULL)
    {
        temp=temp->addr;
        ct2 = ct2 + 1;
    }
    if(ct1 > ct2)
    {
        for(i=1;i<=ct1-ct2;i++)
            head2=insertbegin(head2,0);
    }
    else
    {
       for(i=1;i<=ct2-ct1;i++)
            head1=insertbegin(head1,0);
    }
}

void display(NODE head)
{
    NODE temp;
    if(head->addr == NULL)
        printf("\n list is empty");
    else
    {
        temp=head->addr;
        while(temp!=NULL)
        {
            printf("%d",temp->data);
            temp=temp->addr;
        }
    }
}

NODE reverse(NODE head)
{
    NODE prev,cur,next;
    cur=head->addr;
    prev=NULL;
    while(cur!=NULL)
    {
        next=cur->addr;
        cur->addr=prev;
        prev=cur;
        cur=next;
    }
    head->addr=prev;
    return head;
}

void add(NODE head1,NODE head2)
{
    NODE head,t1,t2;
    int sum=0,carry=0,x;
    head=(NODE)malloc(sizeof(struct node));
    head->addr=NULL;
    head1=reverse(head1);
    head2=reverse(head2);
    t1=head1->addr;
    t2=head2->addr;
    while(t1!=NULL && t2!=NULL)
    {
        x = t1->data + t2->data + carry;
        sum = x  % 10;
        carry = x / 10;
        head=insertbegin(head,sum);
        t1=t1->addr;
        t2=t2->addr;
    }
    if(carry > 0)
        head=insertbegin(head,carry);
    printf("\n The resultant number is\n");
    display(head);

}

int main()
{
    char first[20],second[20];
    int i;
    NODE head1,head2;
    head1=(NODE)malloc(sizeof(struct node));
    head1->addr=NULL;
    head2=(NODE)malloc(sizeof(struct node));
    head2->addr = NULL;
    printf("\n Read first number\n");
    scanf("%s",first);
    for(i=0;first[i]!='\0';i++)
    {
        head1=insertend(head1,first[i] - '0');
    }
    printf("\n The first number is\n");
    display(head1);
    printf("\n Read second number\n");
    scanf("%s",second);
    for(i=0;second[i]!='\0';i++)
    {
        head2=insertend(head2,second[i] - '0');
    }
    printf("\n The second number is\n");
    display(head2);
    appendzero(head1,head2);
    printf("\n The first number is\n");
    display(head1);
    printf("\n The second number is\n");
    display(head2);
    add(head1,head2);
    return 0;
}
