#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	
	int data;
	struct node* next;
	
}NODE;

typedef struct linkedList{
	
	NODE* head;
	NODE* tail;
	
}LINKEDLIST;

LINKEDLIST createList();
NODE * createNode(int data);
void insertFront(LINKEDLIST* linkedList,int data);
void printList(LINKEDLIST linkedList);
void insertFront(LINKEDLIST* linkedList,int data);
void insertRear(LINKEDLIST* linkedList, int data);
void insertAt(LINKEDLIST* linkedList, int data, int index);
void insertSorted(LINKEDLIST* linkedList, int data);
void deleteFront(LINKEDLIST* linkedList);
void deleteRear(LINKEDLIST* linkedList);
void deleteAt(LINKEDLIST* linkedList, int index);
void clearList(LINKEDLIST* linkedList);
void sortList(LINKEDLIST* linkedList);
void swap(NODE* a, NODE* b);
int size(LINKEDLIST* linkedList);
int* toArray(LINKEDLIST* linkedList);
int contains(LINKEDLIST* linkedList, int value);
int get(LINKEDLIST* linkedList, int index);
void set(LINKEDLIST* linkedList, int index, int data);
int getFirstOccurence(LINKEDLIST* linkedList, int data);
int getLastOccurence(LINKEDLIST* linkedList, int data);

int main(void){
	
	LINKEDLIST linkedList = createList();	
	insertRear(&linkedList, 1);
	insertRear(&linkedList, 2);
	insertAt(&linkedList, 7, 0);
	insertAt(&linkedList, 1, 0);
	insertAt(&linkedList, 11, 1);
	sortList(&linkedList);
	

	printList(linkedList);
	return 0;
}

LINKEDLIST createList(){
	
	// This function allocates memory for new linkedlist.
	// returns new empty linkedlist.
	LINKEDLIST linkedList ;
	linkedList.head = (NODE*)malloc(sizeof(NODE));
	linkedList.head = NULL;
	linkedList.tail = (NODE*)malloc(sizeof(NODE));
	linkedList.tail = NULL;
	
	return linkedList;
	
}

NODE * createNode(int data){
	
	// This function allocates memory for new node.
	// Parameter(s) : data---> int value of the node.
	// returns new node which holds int data. 
	NODE* newNode = (NODE*)malloc(sizeof(NODE*));
	newNode->data= data;
	newNode->next= NULL;
	return newNode;
	
}


void insertFront(LINKEDLIST* linkedList,int data){
	
	// This function inserts new node at front of the linkedlist with O(1) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of the new node to be inserted
	
	NODE* newNode = createNode(data);
	
	if(linkedList->head == NULL){
		(linkedList->head) = newNode;
		(linkedList->tail) = newNode;
		return;
	}
	
	newNode->next = linkedList->head;
	linkedList->head = newNode;
	
}

void printList(LINKEDLIST linkedList){
	
	// prints list from head to tail
	
	NODE* tmp = linkedList.head;
	
	while(tmp != NULL){
		
		printf("%d ",tmp->data);
		tmp= tmp->next;
	}
	
}

void insertRear(LINKEDLIST* linkedList, int data){
	
	// This function inserts new node at rear of the linkedlist with O(1) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of the new node to be inserted
	
	NODE* newNode = createNode(data);
	
	if(linkedList->head == NULL){
		
		linkedList->head = newNode;
		linkedList->tail = newNode;
		return;
	}
	
	NODE* tmp = linkedList->tail;
	linkedList->tail = newNode;
	tmp->next = newNode;
	
}

void insertAt(LINKEDLIST* linkedList, int data, int index){
	
	// This function inserts new node at specific position of the linkedlist with O(N) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of the new node to be inserted, index ---> int value of position where node will be inserted
	
	NODE* newNode = createNode(data);
	NODE* tmp = linkedList->head;
	int i=0;
	
	if(index == 0){
		insertFront(linkedList, data);
		return;
	}
	
	while(i<index-1 && tmp->next!=NULL){
		
		tmp= tmp->next;
		i++;
		
	}
	
	if(i < index-1 && tmp->next == NULL){
		
		printf("Index Out Of Bounds");
		return;
			
	}
	
	newNode->next = tmp->next;
	tmp->next = newNode;
	
}

void insertSorted(LINKEDLIST* linkedList, int data){
	
	// Make sure the linkedlist is already sorted.
	// This function inserts new node at proper position of the linkedlist with O(N) complexity. And keeps the list sorted.
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of the new node to be inserted
	
	
	if(data < linkedList->head->data){
		insertFront(linkedList, data);
		return;
	}
	if(data > linkedList->tail->data){
		insertRear(linkedList, data);
		return;
	}
	
	NODE* tmp = linkedList->head;
	NODE* tmp2 = createNode(data);
	while(tmp->next->data < data && tmp->next->next !=NULL){
		tmp=tmp->next;
	}
	
	tmp2->next= tmp->next;
	tmp->next = tmp2;
	
}

void deleteFront(LINKEDLIST* linkedList){
	
	// This function deleted node at front of the linkedlist with O(1) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList.
	
	NODE* tmp = linkedList->head;
	
	if(linkedList->head == NULL){
		
		printf("Can't delete an item. List is already empty");
		return ;
		
	}
	
	if(linkedList->head->next == NULL){
		
		linkedList->head = NULL;
		linkedList->tail = NULL;
		free(tmp);
		return;
		
	}
	

	linkedList->head = tmp->next;
	free(tmp);
	
	
}

void deleteRear(LINKEDLIST* linkedList){
	
	// This function deleted node at rear of the linkedlist with O(N) complexity.( complexity can be upgraded to O(1) with using doubly linkedlist.
	// Parameter(s) : linkedList ---> address of a linkedList. 
	
	NODE* tmp = linkedList->head;
	
	if(linkedList->head == NULL){
		
		printf("Can't delete an item. List is already empty");
		return ;
		
	}
	
	
	if(linkedList->head->next == NULL){
		
		
		linkedList->head = NULL;
		linkedList->tail = NULL;
		free(tmp);
		return;
		
	}
	
	while(tmp->next->next !=NULL){
		
		tmp = tmp->next;
		
	}
	
	NODE* tmp2 = tmp->next;
	tmp->next = NULL;
	free(tmp2);
	
}

void deleteAt(LINKEDLIST* linkedList, int index){
	
	// This function deleted node at specific of the linkedlist with O(N) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList, index ---> int value of position where node will be deleted. 
	
	if(index < 0){
		
		printf("The index to be deleted can't be negative !!!");
		return;
	}
	
	if(index == 0){
		
		deleteFront(linkedList);
		return ;
		
	}
	
	int i=0;
	NODE* tmp = linkedList->head;
	

	while(i< index-1 && tmp->next!=NULL){
	
	i++;
	tmp=tmp->next;
	}
	
	if(i<= index-1 && tmp->next ==NULL){
		
		printf("Index out of bounds !!!");
		return;
	}
	
	NODE* tmp2 = tmp->next;
	tmp->next= tmp->next->next;
	free(tmp2);
}

void clearList(LINKEDLIST* linkedList){
	
	// This function deletes all nodes from linkedlist.
	// Parameter(s) : linkedList ---> address of a linkedList.
	
	NODE* tmp = linkedList->head;
	NODE* tmp2;
	
	if(linkedList->head == linkedList->tail){
		free(tmp);
	}else{	
		while(tmp->next !=NULL){
		
			tmp2= tmp->next;
			free(tmp);
		}
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	
}

void sortList(LINKEDLIST* linkedList){
	
	// This function sorts linkedlist using bubblesort with O(N) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList. 
	
	int swapped=1;
	NODE* tmp = linkedList->head;
	
	if(linkedList->head == NULL){
		return;
	}
	
	while(swapped == 1){
		
		swapped = 0;
		
		while(tmp->next!=NULL){
			
			if(tmp->data > tmp->next->data){
				swap(tmp, tmp->next);
				swapped = 1;
			}
			tmp= tmp->next;
			
		}
		tmp = linkedList->head;
		
	}
	
	
}

void swap(NODE* a, NODE* b){
	
	int tmp = a->data;
	a->data = b->data;
	b->data = tmp;
	
}

int size(LINKEDLIST* linkedList){
	
	// This function returns the size of linkedlist
	// Parameter(s) : linkedList ---> address of a linkedList.
	// Returns number of elements of linkedlist.
	
	if(linkedList->head == NULL){
		return 0;
	}	
	
	NODE* tmp = linkedList->head;
	int count = 1;
		
	while(tmp->next !=NULL){
		
		tmp = tmp->next;
		count ++;
	}
	
	return count;
	
}

int* toArray(LINKEDLIST* linkedList){
	
	// This function creates new array using values of linkedlist.
	// Parameter(s) : linkedList ---> address of a linkedList.
	// Returns : int* new array.
	
	if(linkedList->head ==NULL){
		printf("Error list is empty !!!");
		return NULL;
	}
	
	int* arr = (int*)malloc(sizeof(int)* size(linkedList));
	NODE* tmp= linkedList->head;
	int i=0;
	
	while(tmp!=NULL){
		arr[i] = tmp->data;
		i++;
		tmp=tmp->next;
	}
	
	return arr;
	
}

int contains(LINKEDLIST* linkedList, int value){
	
	// This function searches the value in linkedlist with O(N) complexity.
	// Parameter(s) : linkedList ---> address of a linkedList, value ---> int value of a value to be searched.
	// Returns 1 if linkedlist contains the value, return 0 if linkedlist doesn't contain value.
	
	NODE* tmp = linkedList->head;
	
	while(tmp !=NULL && tmp->data != value){
		tmp = tmp->next;
	}
	
	if(tmp!=NULL){
		return 1;
	}
	
	return 0;
	
}

int get(LINKEDLIST* linkedList, int index){
	
	// This function returns the value in specific index of linkedlist.
	// Parameter(s) : linkedList ---> address of a linkedList, index ---> int value of an index of a linkedlist.
	// Returns if linkedlist containt value returns value of an index, else returns prints error message and returns random value.
	
	if(index < 0){
		
		printf("Negative index is not possible !!!");
		return ;
		
	}
	
	int i=0;
	NODE* tmp = linkedList->head;
	
	while(tmp!=NULL && i< index){
		tmp = tmp->next;
		i++;
	}
	
	if(tmp == NULL){
		printf("Index Out Of Bounds");
		return ;
	}
	
	
	return tmp->data;
}

void set(LINKEDLIST* linkedList, int index, int data){
	
	// This function changes the value in specific index of linkedlist.
	// Parameter(s) : linkedList ---> address of a linkedList, index ---> int value of an index of a linkedlist, data ---> int value to be added to linkedlist
	
	if(index < 0){
		
		printf("Negative index is not possible !!!");
		return ;
		
	}
	
	int i=0;
	NODE* tmp = linkedList->head;
	
	while(tmp!=NULL && i< index){
		tmp = tmp->next;
		i++;
	}
	
	if(tmp == NULL){
		printf("Index out of Bounds");
		return;
	}
	
	tmp->data = data;
}

int getFirstOccurence(LINKEDLIST* linkedList, int data){
	
	// This function returns the index of an wanted values first occurence at linkedlist
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of an index of linkedlist
	// Returns if linkedlist contains value returns the index of first occurence, else returns -1
	
	NODE* tmp = linkedList->head;
	int i=0;
	
	while(tmp!=NULL && tmp->data != data){
		tmp = tmp->next;
		i++;
	}
	
	if(tmp == NULL){
		return -1;
	}
	
	return i;
}

int getLastOccurence(LINKEDLIST* linkedList, int data){
	
	// This function returns the index of an wanted values last occurence at linkedlist
	// Parameter(s) : linkedList ---> address of a linkedList, data ---> int value of an index of linkedlist
	// Returns if linkedlist contains value returns the index of last occurence, else returns -1
	
	NODE* tmp = linkedList->head;
	int i=0, last=-1;
	
	while(tmp !=NULL){
		if(tmp->data == data){
			last = i;
		}
		i++;
		tmp=tmp->next;
	}
	return last;
}

