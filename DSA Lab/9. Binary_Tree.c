#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node *NODE;

NODE create_node(int item)
{
    NODE temp;
    temp=(NODE)malloc(sizeof(struct node));
    temp->data=item;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

NODE insertleft(NODE root,int item)
{
    root->left=create_node(item);
    return root->left;
}

NODE insertright(NODE root,int item)
{
    root->right=create_node(item);
    return root->right;
}

void display(NODE root)
{
    if(root!=NULL)
    {
        display(root->left);
        printf("%d\t",root->data);
        display(root->right);
    }
}

int count_nodes(NODE root)
{
   if (root == NULL)
        return 0;
   else
    return (count_nodes(root->left) + count_nodes(root->right) + 1);
}

int height(NODE root)
{
    int leftht,rightht;
    if(root == NULL)
        return 0;
    else
    {
        leftht = height(root->left);
        rightht = height(root->right);
        if(leftht > rightht)
         return leftht + 1;
        else
         return rightht + 1;
    }
}

int leaf_nodes(NODE root)
{
    if(root==NULL)
        return 0;
    else if(root->left == NULL && root->right == NULL)
        return 1;
    else
        return leaf_nodes(root->left) + leaf_nodes(root->right);
}

int nonleaf_nodes(NODE root)
{
    if(root==NULL || (root->left == NULL && root->right == NULL))
        return 0;
    else
        return nonleaf_nodes(root->left) + nonleaf_nodes(root->right) + 1;
}
int main()
{
    NODE root=NULL;
    root=create_node(45);
    insertleft(root,39);
    insertright(root,78);
    insertleft(root->right,54);
    insertright(root->right,79);
    insertright(root->right->left,55);
    insertright(root->right->right,80);
    printf("\n The tree(inorder) is\n");
    display(root);
    printf("\n");
    printf("\n The total number of nodes is %d\n",count_nodes(root));
    printf("\n The height of the tree is %d\n",height(root));
    printf("\n The total number of leaf nodes is %d\n",leaf_nodes(root));
    printf("\n The total number of non-leaf nodes is %d\n",nonleaf_nodes(root));
    return 0;
}
