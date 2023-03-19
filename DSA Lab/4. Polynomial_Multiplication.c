#include<stdio.h>
#include<stdlib.h>

struct node{
    int coff;
    int expo;
    struct node *next;
};

struct node *getnode(int c, int x){
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    p->coff= c;
    p->expo = x;
    p->next = NULL;
    return p;
}

struct node *insertend(struct node *poly, int c, int x){
    struct node *p;
    p = getnode(c, x);
    
    if(poly == NULL)
        poly = p;
    else {
        struct node *q;
        q = poly;
        while(q->next != NULL)
            q = q->next;
        q->next = p;
    }
    return poly;
}

void display(struct node *poly){
    if(poly == NULL)
        printf("\nempty list");
    else {
        struct node *q;
        q = poly;
        while(q->next != NULL){
            printf("%dx%d  + ", q->coff, q->expo);
            q = q->next;
        }
        printf("%dx%d", q->coff, q->expo);
    }
}

struct node *createpoly(struct node *poly){
    struct node *p;
    int n, c, x;

    printf("\nenter the number of terms: ");
    scanf("%d", &n);
    printf("enter terms from lowest to highest...\n");
    for(int i = 1; i<=n; i++){
        printf("enter coeff and expo value of %d term: ", i);
        scanf("%d%d", &c, &x);
        p = getnode(c, x);
        if(poly == NULL)
            poly = p;
        else {
            p->next = poly;
            poly = p;
        }       
    }
    return poly;
}

struct node *multiplypoly(struct node *poly1, struct node *poly2){
    struct node *result;
    struct node *p1, *p2;
    int res_c, res_x;
    result = NULL;
  
    if(poly1 == NULL)
        return poly2;
    else {
        if(poly2 == NULL)
            return poly1;
        else {
            for(p1=poly1; p1!= NULL; p1=p1->next){
                for(p2=poly2; p2!=NULL; p2=p2->next){
                    res_c = p1->coff * p2->coff;
                    res_x = p1->expo + p2->expo;
                    result = insertend(result, res_c, res_x);
                }
            }
        }
    }
    return result;
}

struct node *reducepoly(struct node *result){
    struct node *p, *q, *temp;
    if(result != NULL){
        for(p=result; p->next!=NULL; p=p->next){
            for(q=p; q!=NULL; q=q->next){
                temp = q->next;
                while(temp!=NULL && p->expo == temp->expo){
                    p->coff = p->coff + temp->coff;
                    q->next = temp->next;
                    free(temp);
                    temp = q->next;
                }  
            }
        }
    }
    return result;
}

int main(){
    struct node *poly1, *poly2, *result;
    poly1 = poly2 = result = NULL;
    
    printf("Create polynomial 1:");
    poly1 = createpoly(poly1);
    printf("Create polynomial 2:");
    poly2 = createpoly(poly2);
    
    printf("\npolynomial 1: ");
    display(poly1);
    printf("\npolynomial 2: ");
    display(poly2);
    
    result = multiplypoly(poly1, poly2);
    
    printf("\nresultant polynomial: ");
    display(result);
    
    printf("\nreduced polynomial: ");
    result = reducepoly(result);
    display(result);
    return 0;
}