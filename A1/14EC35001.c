/*
Author : Prerit Gupta
Roll No : 14EC35001 
email ID : gprerit96@gmail.com
*/ 

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int val;
	struct _node* next;
}node;

typedef struct _stack{
	int top;
	node* list;
}stack;

void push(stack *A,int value)
{
	node *new;
	new = (node*)malloc(sizeof(node));
	new->val = value;
	new->next = NULL;
	if(A->top==-1)
	{
		A->top++;
		A->list = new;
	}
	else{
		A->top++;
		new->next = A->list;
		A->list = new;
	}
}
int pop(stack *A)
{
	int value;
	if(A->top==-1)
		return(-1);
	else{
		A->top--;
		node* top_node = A->list;
		value = A->list->val;
		A->list = A->list->next;
		free(top_node);
		return value;
	}
}
int Ack(int m,int n)
{
	stack *A = (stack*)malloc(sizeof(stack));
	A->top = -1;
	A->list = NULL;
	while(1)
	{
		if(m==0)
		{
			n++;
			if(A->top==-1)
				break;
			m = pop(A);
			continue;
		}
		if(n==0)
		{
			m--;
			n++;
			continue;
		}
		push(A,m-1);
		n--;
	}
	return n;
}
int main()
{
	int m,n;
	printf("Enter the value of m = ");
	scanf("%d",&m);
	printf("\nEnter the value of n = ");
	scanf("%d",&n);
	printf("\nThe Ackerman function value A(%d,%d) = %d\n",m,n,Ack(m,n));
	return 0;
}