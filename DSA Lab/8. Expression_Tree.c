/* Given a String representing a parentheses-free infix arithmetic expression, 
   implement a program to place it in a tree in the infix form. 
   Assume that a variable name is a single letter. 
   Traverse the tree to produce an equivalent postfix and prefix expression string.*/

#include<stdio.h>
#include<stdlib.h>
#define MAX 20

struct node {
    char key;
    struct node *leftchild;
    struct node *rightchild;
};

struct node *root;

struct stack{
    struct node *nodeptrs[MAX];
    int top;
};

void push(struct stack *s, struct node *p){
    s->nodeptrs[++(s->top)] = p;
}

struct node *pop(struct stack *s){
    return(s->nodeptrs[s->top--]);
}

struct node *getnode(char val){
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    p->key = val;
    p->leftchild = p->rightchild = NULL;
    return p;
}

void inorder(struct node *root){
    if(root != NULL){
        inorder(root->leftchild);
        printf("%c  ", root->key);
        inorder(root->rightchild);
    }
}

void preorder(struct node *root){
    if(root != NULL){
        printf("%c  ", root->key);
        preorder(root->leftchild);
        preorder(root->rightchild);
    }
}

void postorder(struct node *root){
    if(root != NULL){
        postorder(root->leftchild);
        postorder(root->rightchild);
        printf("%c  ", root->key);
    }
}

int prcd(char op1, char op2){
    if((op1=='+' || op1=='-') && (op2=='+' || op2=='-'))
        return 1;
    if((op1=='*' || op1=='/') && (op2=='/' || op2=='*'))
        return 1;
    if((op1=='*' || op1=='/') && (op2=='+' || op2=='-'))
        return 1;
    if(op1=='$' && (op2=='+' || op2=='-' || op2=='*' || op2=='/'))
        return 1;
    if((op1=='+' || op1=='-') && (op2=='*' || op2=='/'))
        return 0;
    if(op1=='$' && op2=='$')
        return 0;
    if((op1=='+' || op1=='-' || op1=='*' || op1=='/') && op2=='$')
        return 0;
}

void createexptree(){
    struct stack treestack;
    struct stack opstack;
    char infixexp[MAX];
    char symb;
    struct node *p, *q;
    
    root = NULL;
    treestack.top = opstack.top = -1;
    
    printf("enter a valid parentheses-free infix arithmetic expression: \n ");
    scanf("%s", infixexp);
    
    for(int i=0; infixexp[i]!='\0'; i++){
        symb = infixexp[i];
        if((symb>='a' && symb<='z') || (symb>='A' && symb<='Z')){
            p = getnode(symb);
            push(&treestack, p);
        }
        else {
            while((opstack.top != -1) && prcd(opstack.nodeptrs[opstack.top]->key, symb)){
                q = pop(&opstack);
                q->rightchild = pop(&treestack);
                q->leftchild = pop(&treestack);
                push(&treestack, q);
            }
            p = getnode(symb);
            push(&opstack, p);
        }
    }
    while(opstack.top != -1){
        q = pop(&opstack);
        q->rightchild = pop(&treestack);
        q->leftchild = pop(&treestack);
        push(&treestack, q);
    }
    root = pop(&treestack);
}

int main(){
    
    printf("Expression tree construction:\n");
    createexptree();
    
    printf("\nInorder traversal:  ");
    inorder(root);
    
    printf("\nPreorder traversal:  ");
    preorder(root);
    
    printf("\nPostorder traversal:  ");
    postorder(root);
    
    return 0;
}
