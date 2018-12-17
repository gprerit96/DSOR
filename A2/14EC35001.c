/*
Author : Prerit Gupta
Roll No : 14EC35001 
email ID : gprerit96@gmail.com
Title : Traverse binary tree in pre-order and post-order manner respectively
*/

#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

typedef struct _node{
	int info;
	struct _node *left,*right;
}node;

struct Queue
{
    int front, rear, size;
    unsigned capacity;
    node** array;
};
 
// function to create a queue of given capacity. 
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0; 
    queue->rear = capacity - 1;  // This is important, see the enqueue
    queue->array = (node**) malloc(queue->capacity * sizeof(node*));
    return queue;
}
 
// Queue is full when size becomes equal to the capacity 
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{  return (queue->size == 0); }
 
// Function to add an item to the queue.  
// It changes rear and size
void enqueue(struct Queue* queue, node* item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
 
// Function to remove an item from queue. 
// It changes front and size
node* dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    node* item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
typedef struct _snode {
	node* val;
	struct _snode* next;
}snode;

typedef struct _stack{
	int top;
	snode* list;
}stack;

void push(stack *A,node* value)
{
	snode *new;
	new = (snode*)malloc(sizeof(snode));
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
node* pop(stack *A)
{
	node* value;
	if(A->top==-1)
		return NULL;
	else{
		A->top--;
		snode* top_node = A->list;
		value = A->list->val;
		A->list = A->list->next;
		free(top_node);
		return value;
	}
}
int isStackEmpty(stack *A)
{
	return (A->top==-1);
}


node* getNode(int x)
{
    node *p = (node*)malloc(sizeof(node));
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return p;

}
void CreateTree(node* root,int row_limit)
{
    int len,cnt =1;
    struct Queue* s = createQueue(1000);
    //while(!s.empty())
    //    s.pop();
    enqueue(s,root);
    while(row_limit>0)
    {
        len = s->size;
        while(len)
        {
            node* p = s->array[s->front];
            if(p->left==NULL)
            {
                p->left = getNode(++cnt);
                enqueue(s,p->left);
            }

            if(p->right==NULL)
            {
                 p->right = getNode(++cnt);
                 enqueue(s,p->right);
            }
            node *f = dequeue(s);
            len--;
        }
        row_limit--;
    printf("rowlimit : %d\n",row_limit);
    }
}

void PreOrder(node* root)
{
    // Check for empty tree
    if (root == NULL)
        return;
    node* temp;	
	stack *A = (stack*)malloc(sizeof(stack));
	A->top = -1;
	A->list = NULL;
    //stk.push(root);
    do{
        if(root!=NULL){
            printf(" %d",root->info);
            push(A,root);
            root=root->left;
        }
        else
        {
           temp = A->list->val;
           root = temp->right;
           pop(A);
           if((root==NULL)&&(!isStackEmpty(A)))
            {
	            temp = A->list->val;
	            root=temp->right;
	            pop(A);
            }

        }
    }while((!isStackEmpty(A))||(root!=NULL));
    printf("\nPreOrder Traversal printed!\n");
}
void InOrder(node* root)
{
	// Check for empty tree
    if (root == NULL)
        return;
	node* temp;
	stack *A = (stack*)malloc(sizeof(stack));
	A->top = -1;
	A->list = NULL;
    do{
        if(root!=NULL){
            push(A,root);
            root=root->left;
        }
        else
        {
           temp = A->list->val;
           printf(" %d",temp->info);
           root = temp->right;
           pop(A);
           if((root==NULL)&&(!isStackEmpty(A)))
            {
	            temp = A->list->val;
	            printf(" %d",temp->info);
	            root=temp->right;
	            pop(A);
            }

        }
    }while((!isStackEmpty(A))||(root!=NULL));
    printf("\n InOrder Traversal printed!\n");
}

void PostOrder(node* root)
{
	// Check for empty tree
    if (root == NULL)
        return;
	node* temp;
	stack *A = (stack*)malloc(sizeof(stack));
	A->top = -1;
	A->list = NULL;
    do{
        if(root!=NULL){
        	if(root->right!=NULL)
        		push(A,root->right);
            push(A,root);
            root=root->left;
        }
        else
        {
           temp = A->list->val;
           root = temp->right;
           pop(A);
           if((root!=NULL)&&(!isStackEmpty(A))&&(A->list->val == root))
            {
	            pop(A);
	            push(A,temp);
            }
            else
            {
            	printf("%d ", temp->info);
            	root = NULL;
            }

        }
    }while((!isStackEmpty(A))||(root!=NULL));
    printf("\n PostOrder Traversal printed!\n");
}
int main()
{
    node* root = getNode(1);
    // Create a tree with 31 nodes
	//          1
    //        2   3
    //      4  5 6  7
    //     .... and so one till 31 nodes
    CreateTree(root,4);
    PreOrder(root);
    InOrder(root);
    PostOrder(root);
    
    return 0;
}
