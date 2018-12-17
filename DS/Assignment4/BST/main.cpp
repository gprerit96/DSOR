#include<iostream>
#include<cstdlib>
using namespace std;

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key)
{
    struct Node* node=(struct Node*)malloc(sizeof(struct Node));
    node->data=key;
    node->left=NULL;
    node->right=NULL;
    return node;
}

void insertNode(struct Node*& root, int key)
{
    struct Node *node=newNode(key);
    struct Node *parent=NULL;
    struct Node *curr=root;
    if(curr==NULL)
    {
        root=node;
        return;
    }
    while(curr!=NULL)
    {
        parent=curr;
        if(key>curr->data) curr=curr->right;
        else
            curr=curr->left;
    }
    if(parent->data<key)
        parent->right=node;
    else parent->left=node;

}

void printInorder(struct Node* root)
{
    if(root==NULL)
        return;
    printInorder(root->left);
    cout<<root->data<<" ";
    printInorder(root->right);
}

struct Node* minNode(struct Node* root)
{
        struct Node* node=NULL;
        if(root==NULL) return NULL;
        while(root->left!=NULL)
            root=root->left;
        node=root;
        return node;
}

struct Node* deleteNode(struct Node* root, int key)
{
    if(root==NULL)
        {
            cout<<"KEY NOT FOUND"<<endl;
            return root;
        }
    else if(key>root->data) root->right=deleteNode(root->right,key);
    else if(key<root->data) root->left=deleteNode(root->left,key);
    else
    {
        if(root->left==NULL&&root->right==NULL)
        {
           free(root);
            return NULL;
        }

        else if(root->left==NULL&&root->right!=NULL) return root->right;

        else if(root->left!=NULL&&root->right==NULL) return root->left;

        else
        {
            struct Node* temp=minNode(root->right);
            root->data=temp->data;
            temp->data=key;
            root->right=deleteNode(root->right,key);
        }
    }
}

bool findKey(struct Node* root, int key)
{
    if(root==NULL)
        return false;
    else if(root->data==key) return true;
    else if(root->data<key) findKey(root->right,key);
    else findKey(root->left, key);
}

int main()
{
    int operation=0, key;
    struct Node* root=NULL;

    while(1)
    {
        cin>>operation;
        if(operation>=4||operation<=0) break;
        cin>>key;
        if(operation==1)
            insertNode(root,key);
        else if(operation==2)
            deleteNode(root,key);
        else if(operation==3)
            {
                if(findKey(root,key))
                    cout<<"TRUE"<<endl;
                else cout<<"FALSE"<<endl;
            }

        printInorder(root);
        cout<<endl;
    }
    if(operation<1||operation>4) cout<<"INVALID INPUT"<<endl;
    return 0;
}
