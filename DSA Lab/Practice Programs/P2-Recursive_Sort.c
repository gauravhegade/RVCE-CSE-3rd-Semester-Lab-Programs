#include <stdio.h>
#include <stdlib.h>
int sort_check(int a[10],int n)
{
    if(n==1)
        return 1;
    if (a[n-1]<a[n-2])
        return  0;
     else
         return sort_check(a,n-1);
}
int main()
{
    int n,i,a[10],flag=0;
    printf("\n Read the size of array :");
    scanf("%d",&n);
    printf("\n Read elements\n");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    flag=sort_check(a,n);
    if(flag == 1)
        printf("\n Sorted");
    else
        printf("\n Not sorted");
    return 0;
}
