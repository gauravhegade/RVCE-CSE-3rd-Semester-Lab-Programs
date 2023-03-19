#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE 10

struct stack
{
    int top;
    float data[SIZE];
};
typedef struct stack STACK;

void push(STACK *s,float item)
{
    s->data[++(s->top)]=item;
}

float pop(STACK *s)
{
    return s->data[(s->top)--];
}

float operate(float op1,float op2,char symbol)
{
    switch(symbol)
    {
        case '+' : return op1 + op2;
        case '-' : return op1 - op2;
        case '*' : return op1 * op2;
        case '/' : return op1 / op2;
    }
}

float evalprefix(STACK *s,char prefix[10])
{
    char symbol;
    float op1,op2,res;
    int i;
    for(i=strlen(prefix)-1;i>=0;i--)
    {
        symbol=prefix[i];
        if(isdigit(symbol))
            push(s,symbol-'0');
        else
        {
            op1=pop(s);
            op2=pop(s);
            res=operate(op1,op2,symbol);
            push(s,res);
        }
    }
    return pop(s);
}

int main()
{
    char prefix[10];
    float ans;
    STACK s;
    s.top=-1;
    printf("\n Read the postfix expression\n");
    scanf("%s",prefix);
    ans=evalprefix(&s,prefix);
    printf("\n The final answer is %f\n",ans);
    return 0;
}
