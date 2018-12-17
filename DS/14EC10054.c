#include <stdio.h>
#define MAXSIZE 100
 
struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK; //defining Stack

STACK s;    //Creating a stack
 
void push(int); //initialising functions
int  pop(void);
int exponent(int);
 
int main (void)
{
    int m,n;

    printf("Enter m and n: ");
    scanf("%d %d",&m,&n);   //taking input from user

    s.top = -1; //setting top value as -1 when stack is empty
    int i=m;
    int j=n;
 
    while (i>=1)
    {
        if(i==1){
            j=exponent(j);
            i=pop();
        }

        if(j==1 && i>=2){
            i=i-1;
            j=2;
        }

        if(i>=2 && j>=2){
            push(i-1);
            j=j-1;
        }
    }

    if (i==-1)
        printf("Output - Integer(Result): %d\n",j);
        
    return 0;
}


/*  Function to add an element to the stack */
void push (int num)
{
    if (s.top == (MAXSIZE - 1))
    {
        return; //can't push more elements : Overflow
    }
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = num;
    }
    return;
}


/*  Function to delete an element from the stack */
int pop ()
{
    int num;
    if (s.top == - 1)
    {
        return (s.top); //returns -1 is stack is already empty: Underflow
    }
    else
    {
        num = s.stk[s.top];
        s.top = s.top - 1;
    }
    return(num);
}

/*Function to find the value of 2^j*/
int exponent(int n){
    int i=0;
    int num=1;

    for (i=1;i<=n;i++){
        num=num*2;
    }

    return num;
}
