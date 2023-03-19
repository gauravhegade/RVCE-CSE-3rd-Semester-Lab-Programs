#include<stdio.h>
#define MAX 15

int h[MAX], n=0; // n-total number of elements in the heap

void max_heapify( ){
    int k, v, heap, i, j;
    for (i = n/2; i >= 1; i--) {
        k = i;
        v = h[k];       
        heap = 0; 
        while(!heap && 2*k<=n){
            j = 2*k;
            if(j<n) {
                //then two children
                if(h[j] < h[j+1])
                    j = j+1;
            }
            if(v >= h[j])
                heap = 1;
            else {
                h[k] = h[j];
                k = j;
            }
	}//end while
        h[k] = v;
    }//end for
}   
 
void insertpq(int ele) {
    if (n > MAX ) {
        printf("\nOverflow: The heap is full. Cannot insert");
        return;
    }
    
    h[n+1] = ele; // insert the new element at the last position of the array 
    n = n + 1;    // increase the number of elements count by 1

    max_heapify(); // heapify
}

// delete max element
void deletemax() {
    if(n == 0){
        printf("\nUnderflow: The heap is empty. Cannot delete");
        return;
    }
        
    printf("\nThe maximum element deleted: %d", h[1]);
    
    h[1] = h[n]; // replace the root element with the last element
    n = n - 1;   // decrease the number of elements count by 1

    max_heapify(); // heapify
}

void display() {
    if(n == 0){
        printf("\nThe heap is empty!!!");
        return;
    }
    
    printf("\npriority queue contents: ");
    for (int i = 1; i <= n; i++) 
        printf("%d  ", h[i]);
}


int main() {
    int ch, ele;
    while(1){
        printf("\nPriority Queue: 1.Insert, 2.Delete, 3.Display: ");
        scanf("%d", &ch);
        switch(ch){
            case 1: printf("enter the element: ");
                    scanf("%d", &ele);
                    insertpq(ele);
                    display();
                    break;
            case 2: deletemax();
                    display();
                    break;
            case 3: display();
                    break;
            default: return 0;
        }
    }
    return 0;
}