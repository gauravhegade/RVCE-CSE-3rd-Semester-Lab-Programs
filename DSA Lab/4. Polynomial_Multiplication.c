#include <stdio.h>
#include <stdlib.h>
struct node
{
    int co,po;
    struct node *addr;
};
typedef struct node *NODE;

NODE insertend(NODE start,int co,int po)
{
    NODE temp,cur;
    temp=(NODE)malloc(sizeof(struct node));
    temp->co=co;
    temp->po=po;
    temp->addr=NULL;
    if(start == NULL)
        return temp;
    cur=start;
    while(cur->addr!=NULL)
        cur=cur->addr;
    cur->addr=temp;
    return start;
}

void display(NODE start)
{
    NODE temp;
    if(start==NULL)
        printf("\n Polynomial is empty");
    else
     {
         temp=start;
         while(temp->addr!=NULL)
         {
             printf("%d*X^%d+",temp->co,temp->po);
             temp=temp->addr;
          }
          printf("%d*X^%d",temp->co,temp->po);
    }
}

NODE addterm(NODE res,int co,int po)
{
    NODE temp,cur;
    int flag =0;
    temp=(NODE)malloc(sizeof(struct node));
    temp->co=co;
    temp->po=po;
    temp->addr=NULL;
    if(res == NULL)
        return temp;
    cur=res;
    while(cur!=NULL)
    {
        if(cur->po==po)
        {
            cur->co=cur->co+co;
            flag=1;
        }
        cur=cur->addr;
    }
    if(flag==0)
    {
      res=insertend(res,co,po);
    }
    return res;
}
NODE multiplypoly(NODE poly1,NODE poly2)
{
    NODE first,second,res=NULL;
    for(first=poly1;first!=NULL;first=first->addr)
        for(second=poly2;second!=NULL;second=second->addr)
            res=addterm(res,first->co*second->co,first->po+second->po);
    return res;
}
int main()
{
    NODE poly1=NULL,poly2=NULL,res;
    int n,i,co,po;
    printf("\n Read no of terms of first polynomial :");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("\n Read co and po of %d term :",i);
        scanf("%d%d",&co,&po);
        poly1=insertend(poly1,co,po);
    }
    printf("\n The first polynomial is\n");
    display(poly1);
    printf("\n Read no of terms of second polynomial :");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("\n Read co and po of %d term :",i);
        scanf("%d%d",&co,&po);
        poly2=insertend(poly2,co,po);
    }
    printf("\n The first polynomial is\n");
    display(poly1);
    res=multiplypoly(poly1,poly2);
    printf("\n The resultant polynomial is\n");
    display(res);
    return 0;
}
