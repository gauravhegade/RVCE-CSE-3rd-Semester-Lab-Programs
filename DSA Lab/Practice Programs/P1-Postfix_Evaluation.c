#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

float evalpostfix(STACK *s,char postfix[10])
{
    char symbol;
    float op1,op2,res;
    int i;
    for(i=0;postfix[i]!='\0';i++)
    {
        symbol=postfix[i];
        if(isdigit(symbol))
            push(s,symbol-'0');
        else
        {
            op2=pop(s);
            op1=pop(s);
            res=operate(op1,op2,symbol);
            push(s,res);
        }
    }
    return pop(s);
}

int main()
{
    char postfix[10];
    float ans;
    STACK s;
    s.top=-1;
    printf("\n Read the postfix expression\n");
    scanf("%s",postfix);
    ans=evalpostfix(&s,postfix);
    printf("\n The final answer is %f\n",ans);
    return 0;
}
