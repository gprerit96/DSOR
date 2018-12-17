/* Author : Prerit Gupta
   Roll No : 14EC35001
   Title: Program to Insert and delete in height balanced binary tree
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
	int info;
	int height;
	struct _node *left,*right;
}node;

node *get_node(int value)
{
	node *x = (node*)malloc(sizeof(node));
	x->info = value;
	x->left = NULL;
	x->right = NULL;
	x->height = 1;
	return x;
}
int max(int a,int b){
	return a>b?a:b;
}
int height(node *root)
{
	if(root==NULL)
		return 0;
	else
		return root->height;
}
node *Left_Rotate(node *x)
{
	node *y = x->right;
	node *beta = y->left;
	y->left = x;
	x->right = beta;
	x->height = max(height(x->right),height(x->left))+1;
	y->height = max(height(y->right),height(y->left))+1;	
	return y;
}
node *Right_Rotate(node *y)
{
	node *x = y->left;
	node *beta = x->right;
	x->right = y;
	y->left = beta;
	y->height = max(height(y->right),height(y->left))+1;
	x->height = max(height(x->right),height(x->left))+1;
	return x;
}
int balance_value(node *root)
{
	if(root==NULL)
		return 0;
	else
		return height(root->left)-height(root->right);
}
node *Insert(node *root,int value)
{
	if(root==NULL)
		return get_node(value);
	if(value<root->info)
		root->left = Insert(root->left,value);
	else if(value>root->info)
		root->right = Insert(root->right,value);
	else
		return root;
	root->height = max(height(root->left),height(root->right))+1;
	
	int b_val = balance_value(root);
	if(b_val>1&&(value<root->left->info))
		return Right_Rotate(root);
	if(b_val<-1&&(value>root->right->info))
		return Left_Rotate(root);
	if(b_val>1&&(value>root->left->info))
	{
		root->left = Left_Rotate(root->left);
		return Right_Rotate(root);
	}
		
	if(b_val<-1&&(value<root->right->info))
	{	
		root->right = Right_Rotate(root->right);
		return Left_Rotate(root);
	}
	return root;
}
node *Delete(node *root,int value)
{
	if(root==NULL)
	{
		printf("Void Deletion for value %d\n",value);
		return NULL;
	}
	if(root->info==value)
	{
		if(root->right==NULL)
		{
			node *x = root->left;
			free(root);
			return x;
		}
		else{
			node *q = root,*p = root->right;
			int flag = 0;
			while(p->left)
			{
				q = p;
				p = p->left;
				flag = 1;
			}
			root->info = p->info;
			if(flag)
				q->left = p->right;
			else
				q->right = p->right;
			free(p);
			return root;
		}

	}
	else if(value<root->info)
		root->left = Delete(root->left,value);
	else if(value>root->info)
		root->right = Delete(root->right,value);
}
void PreOrder(node *root)
{
	if(root!=NULL)
	{
		printf("%d, ",root->info);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}
int main()
{
	node *root = NULL;

	root = Insert(root, 6); 
	root = Insert(root, 10); 
	root = Insert(root, 35); 
	root = Insert(root, 50); 
	root = Insert(root, 34); 
	root = Insert(root, 45);

	printf("Pre-order Traversal of Height Balanced BST after inserting 6,10,35,50,34,45:\n");
	PreOrder(root);
	printf("\n");

	root = Delete(root, 10);
	root = Delete(root, 35);
	root = Delete(root, 32);

	printf("Pre-order Traversal of Height Balanced BST after deleting 10,35 and 32(which doesn't exist):\n");
	PreOrder(root);
	printf("\n");

	int choice;
	int value;
	do{
		printf("Enter 1 to insert or 2 to delete a node in the BST.\n Pressing any other key will exit.\n ");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("Enter the value: ");
			scanf("%d",&value);
			root = Insert(root, value);
			printf("Pre-order Traversal after inserting %d is :",value);
			PreOrder(root);
			printf("\n");
		}
		if(choice==2)
		{
			printf("Enter the value: ");
			scanf("%d",&value);
			root = Delete(root, value);
			printf("Pre-order Traversal after deleting %d is :",value);
			PreOrder(root);
			printf("\n");
		}

	}while(choice==1||choice==2);

	return 0;
}