#include <stdio.h>
#include <stdlib.h>

typedef struct T_NODE{        // 2-3 Node
	int *f1, *f2;         // fields
	struct T_NODE *parent;
	struct T_NODE *ch1, *ch2, *ch3;  // children
}T_NODE;

T_NODE *newTnode(){
	T_NODE *t = (T_NODE*)malloc(sizeof(T_NODE));
	t->f1 = t->f2 = NULL;
	t->parent = t->ch1 = t->ch2 = t->ch3 = NULL;
	return t;
}

int isEmpty(T_NODE *T){ // All fields are NULL
	if (T->f1 == NULL && T->f2 == NULL){
		if (T->ch2 == NULL && T->ch3 == NULL && T->ch1 == NULL) return 1;
	}
	return 0;
}

int isLeaf(T_NODE *T){    // All fields except 'f1' are NULL. 'f1' contains address of the key
	if (T->ch2 == NULL && T->ch3 == NULL && T->ch1 == NULL){
		if (T->f2 == NULL && T->f1 != NULL) return 1;
	}
	return 0;
}

int IsMember(T_NODE *T, int key, T_NODE **pin){
	if (isEmpty(T)) return 0;
	if (isLeaf(T)){
		if (*T->f1 == key) return 1;
		*pin = T->parent;
		return 0;
	}

	if (T->f1 != NULL && T->f2 == NULL){  // only ch1 and ch2 exist
		if (*T->f1 == key) return 1;
		if (key < *T->f1) return IsMember(T->ch1, key, pin);
		return IsMember(T->ch2, key, pin);
	}
	// All three children present
	if (*T->f1 == key || *T->f2 == key) return 1;
	if (key < *T->f1) return IsMember(T->ch1, key, pin);
	if (key > *T->f1 && key < *T->f2) return IsMember(T->ch2, key, pin);
	return IsMember(T->ch3, key, pin);
}

void setFields(T_NODE *T){
	if (T == NULL) return;
	if (isLeaf(T)) return;
	T_NODE *tmp = T->ch2;
	while(!isLeaf(tmp)){
		tmp = tmp->ch1;
	}
	T->f1 = tmp->f1;  // set field 1

	tmp = T->ch3;
	if (tmp == NULL){
		T->f2 = NULL;
	}
	else{
		while(!isLeaf(tmp)){
			tmp = tmp->ch1;
		}
		T->f2 = tmp->f1;  // set field 2
	}

	setFields(T->ch1);
	setFields(T->ch2);
	setFields(T->ch3);
	return;
}

void balanceTree(T_NODE **pT, T_NODE **pin, T_NODE *temp1, T_NODE *temp2){
	T_NODE *in = *pin;
	T_NODE *t1, *t2, *t3, *t4;
	if (in->parent == NULL){   // if 'in' is the root itself
			T_NODE *newroot = in;
			newroot->ch1 = temp1;
			temp1->parent = newroot;
			newroot->ch2 = temp2;
			temp2->parent = newroot;
			newroot->ch3 = NULL;
			newroot->parent = NULL;
			*pT = newroot;
			setFields(*pT);
			return;
	}
	if (in == in->parent->ch1){
		t1 = temp1;
		t2 = temp2;
		t3 = in->parent->ch2;
		t4 = in->parent->ch3;
	}
	if (in == in->parent->ch2){
		t2 = temp1;
		t3 = temp2;
		t1 = in->parent->ch1;
		t4 = in->parent->ch3;
	}
	if (in == in->parent->ch3){
		t3 = temp1;
		t4 = temp2;
		t1 = in->parent->ch1;
		t2 = in->parent->ch2;
	}
	while (t4 != NULL && in->parent != NULL){
		T_NODE *newparent1 = in->parent;
		T_NODE *newparent2 = in;
		newparent2->parent = newparent1->parent;

		newparent1->ch1 = t1;
		t1->parent = newparent1;
		newparent1->ch2 = t2;
		t2->parent = newparent1;
		newparent1->ch3 = NULL;

		newparent2->ch1 = t3;
		t3->parent = newparent2;
		newparent2->ch2 = t4;
		t4->parent = newparent2;
		newparent2->ch3 = NULL;

		if (newparent1->parent == NULL){  // new root to be allocated for the tree
			T_NODE *newroot = newTnode();
			newroot->ch1 = newparent1;
			newparent1->parent = newroot;
			newroot->ch2 = newparent2;
			newparent2->parent = newroot;
			newroot->ch3 = NULL;
			*pT = newroot;
			in = newroot;
		}
		else{
			if (newparent1 == newparent1->parent->ch1){
				t1 = newparent1;
				t2 = newparent2;
				t3 = newparent1->parent->ch2;
				t4 = newparent1->parent->ch3;
			}
			if (newparent1 == newparent1->parent->ch2){
				t2 = newparent1;
				t3 = newparent2;
				t1 = newparent1->parent->ch1;
				t4 = newparent1->parent->ch3;
			}
			if (newparent1 == newparent1->parent->ch3){
				t3 = newparent1;
				t4 = newparent2;
				t1 = newparent1->parent->ch1;
				t2 = newparent1->parent->ch2;
			}
			in = newparent1;      // shifting the problem upwards
		}

	}
	if (t4 == NULL){           // when while loop stops before reaching the tree root
		T_NODE *newp = in->parent;
		newp->ch1 = t1;
		t1->parent = newp;
		newp->ch2 = t2;
		t2->parent = newp;
		newp->ch3 = t3;
		t3->parent = newp;
	}
	setFields(*pT);
	return;
}

void printkeys(T_NODE *T){
	T_NODE *t = T;
	if (t == NULL) return;
	if (isLeaf(t)){
		printf("%d ", *t->f1);
		return;
	}
	printkeys(T->ch1);
	printkeys(T->ch2);
	printkeys(T->ch3);
	return;
}

void Insert(T_NODE **pT, int *px, T_NODE *in){
	if (px == NULL || pT == NULL) exit(1);
	T_NODE *T = *pT;
	if (isEmpty(T)){   // initial case
		T->f1 = px;
		T->ch2 = newTnode();   // initially only 2nd child
		T->ch2->f1 = px;
		T->ch2->parent = T;
		return;
	}
	if (T->ch1 == NULL && T->ch2 != NULL && T->ch3 == NULL){ // special case
		if (*px <= *T->ch2->f1){  // Insert as 1st child
			T->ch1 = newTnode();
			T->ch1->f1 = px;
			T->ch1->parent = T;
		}
		else{                    // Insert as 2nd child
			T->f1 = px;
			T->ch1 = T->ch2;
			T->ch1->parent = T;
			T->ch2 = newTnode();
			T->ch2->f1 = px;
			T->ch2->parent = T;
			T->f1 = px;
		}
		return;
	}

	if (in->ch3 == NULL){   // only 2 children
		in->ch3 = newTnode();
		in->ch3->parent = in;
		in->ch3->f1 = px;     // default as 3rd child
		T_NODE *tmp;
		if (*px < *in->f1){
			if (*px < *in->ch1->f1){   // insert as 1st child
				tmp = in->ch1;
				in->ch1 = in->ch3;
				in->ch3 = in->ch2;
				in->ch2 = tmp;
				in->f1 = in->ch2->f1;  // adjust fields
				in->f2 = in->ch3->f1;
			}
			else{					// insert as 2nd child
				tmp = in->ch2;
				in->ch2 = in->ch3;
				in->ch3 = tmp;
				in->f1 = in->ch2->f1;  // adjust fields
				in->f2 = in->ch3->f1;
			}
		}
		else{				// insert as 3rd child
			in->f1 = in->ch2->f1;  // adjust fields
			in->f2 = in->ch3->f1;
		}
		setFields(T);
		return;
	}

	// All three children present
	T_NODE *nleaf = newTnode();
	nleaf->f1 = px;				// the new leaf node
	T_NODE *temp1 = newTnode();
	T_NODE *temp2 = newTnode();
	if (*px < *in->f1){			// new leaf goes with 1st half
		if (*px < *in->ch1->f1){     // new leaf as 1st child in 1st half
			temp1->ch1 = nleaf;
			temp1->ch2 = in->ch1;
		}
		else{                        // new leaf as 2nd child in 1st half
			temp1->ch1 = in->ch1;
			temp1->ch2 = nleaf;
		}
		nleaf->parent = temp1;
		in->ch1->parent = temp1;

		temp2->ch1 = in->ch2;    // preparing 2nd half
		temp2->ch2 = in->ch3;
		in->ch2->parent = temp2;
		in->ch3->parent = temp2;
	}
	else{                          // new leaf node goes with second half
		temp1->ch1 = in->ch1;    // preparing 1st half
		temp1->ch2 = in->ch2;
		in->ch1->parent = temp1;
		in->ch2->parent = temp1;

		if (*px < *in->ch3->f1){     // new leaf as 1st child in 2nd half
			temp2->ch1 = nleaf;
			temp2->ch2 = in->ch3;
		}
		else{                        // new leaf as 2nd child in 2nd half
			temp2->ch1 = in->ch3;
			temp2->ch2 = nleaf;
		}
		nleaf->parent = temp2;
		in->ch3->parent = temp2;
	}

	// temp1 and temp2 are the two new nodes to be fitted into the 2-3 Tree
	balanceTree(pT, &in, temp1, temp2);
}

// make a Queue for level order

typedef struct Queue{
	T_NODE *info[100];
	int front, rear;
} Queue;

T_NODE *deleteQ(Queue *pq){
	if ((*pq).rear == (*pq).front) exit(2);
	(*pq).front = ((*pq).front+1)%100;
	return ((*pq).info[(*pq).front]);
}

void insertQ(Queue *pq, T_NODE *k){
	(*pq).rear = ((*pq).rear+1)%100;
	if ((*pq).rear == (*pq).front) exit(2);
	(*pq).info[(*pq).rear] = k;
}


void levelOrder(T_NODE *T){
	Queue qlist;
	qlist.front = qlist.rear = 99;
	insertQ(&qlist, T);
	while(qlist.rear != qlist.front){
		T_NODE *tmp = deleteQ(&qlist);
		if (tmp->ch1!=NULL) insertQ(&qlist, tmp->ch1);
		if (tmp->ch2!=NULL) insertQ(&qlist, tmp->ch2);
		if (tmp->ch3!=NULL) insertQ(&qlist, tmp->ch3);
		if (!isLeaf(tmp)){
			if (tmp->f1 == NULL)printf("(_ ");
			else printf("(%d ", *tmp->f1);
			if (tmp->f2 == NULL)printf("_), ");
			else printf("%d), ", *tmp->f2);
		}
	}
}

int main(){
	int choice, key;
	T_NODE *T = newTnode();
	printf("Insertion: 1\nDeletion: 2\nExit: 3\n");
	int count = 0;
	int store_keys[1000];
	while(1){
		printf("Enter choice of operation and key value, separated by space:\n");
		scanf("%d", &choice);
		if (choice == 3) exit(1);
		scanf("%d", &store_keys[count]);

		if (choice == 1){
			T_NODE *in;
			if (!IsMember(T, store_keys[count], &in))
				Insert(&T, &store_keys[count], in);
			printf ("level order: ");
			levelOrder(T);
			printf("\n");
			printf("leaf nodes: ");
			printkeys(T);
			printf("\n");
		}

		count++;
	}
	return 0;
}
