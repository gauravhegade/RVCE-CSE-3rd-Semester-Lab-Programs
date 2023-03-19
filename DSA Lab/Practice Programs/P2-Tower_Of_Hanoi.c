#include <stdio.h>
#include <stdlib.h>

void tower(int n,char s,char d,char t)
{
    if(n==1)
        printf("\n Move %d disc from %c to %c",n,s,d);
    else
    {
        tower(n-1,s,t,d);
        printf("\n Move %d disc from %c to %c",n,s,d);
        tower(n-1,t,d,s);
    }
}
int main()
{
    int n;
    printf("\n Read no of disc:");
    scanf("%d",&n);
    tower(n,'S','D','T');
    return 0;
}
