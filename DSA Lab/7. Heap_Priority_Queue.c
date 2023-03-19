#include <stdio.h>
#include <stdlib.h>

void heapify(int a[10],int n)
{
    int i,k,v,j,flag=0;
    for(i=n/2;i>=1;i--)
    {
        k=i;
        v=a[k];
        while(!flag && 2*k <= n)
        {
            j=2*k;
            if(j<n)
            {
                if(a[j]<a[j+1])
                    j=j+1;
            }
            if(v>=a[j])
                flag=1;
            else
            {
                a[k]=a[j];
                k=j;
            }
        }
        a[k]=v;
        flag=0;
    }
}

int main()
{
    int n,i,a[10],ch;
    for(;;)
    {
        printf("\n 1. Create Heap");
        printf("\n 2. Extractmax");
        printf("\n 3. Exit");
        printf("\n Read Choice :");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("\n Read no of elements :");
                   scanf("%d",&n);
                   printf("\n Read Elements\n");
                   for(i=1;i<=n;i++)
                    scanf("%d",&a[i]);
                   heapify(a,n);
                   printf("\n Elements after heap\n");
                   for(i=1;i<=n;i++)
                    printf("%d\t",a[i]);
                    break;
            case 2:if(n>=1)
                    {
                        printf("\n Element deleted is %d\n",a[1]);
                        a[1]=a[n];
                        n=n-1;
                        heapify(a,n);
                        if(n!=0)
                        {
                            printf("\n Elements after reconstructing heap\n");
                            for(i=1;i<=n;i++)
                               printf("%d\t",a[i]);
                        }
                    }
                    else
                        printf("\n No element to delete");
                    break;
            default:exit(0);

        }
    }
    return 0;
}
