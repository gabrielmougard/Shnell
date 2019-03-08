#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

void push(struct Node** head_ref, void *new_data, size_t data_size) 
{ 
    // Allocate memory for node 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    new_node->data  = malloc(data_size); 
    new_node->next = (*head_ref); 
  
    // Copy contents of new_data to newly allocated memory. 
    // Assumption: char takes 1 byte. 
    int i; 
    for (i=0; i<data_size; i++) 
        *(char *)(new_node->data + i) = *(char *)(new_data + i); 
  
    // Change head pointer as new node is added at the beginning 
    (*head_ref)    = new_node; 
}

char *linkedListToArray(Node *node) {

    //get the size of the linkedList
    int linkedListSize = getCount(&node);
    char *res = malloc(sizeof(char)*linkedListSize);

    while (node != NULL) 
    { 
        res = node->data); 
        node = node->next;
        res++; //pointer incrementation 
    }

    return res;
}

void printInteger(void *i) 
{ 
   printf(" %d", *(int *)i); 
}

void printFloat(void *f) 
{ 
   printf(" %f", *(float *)f); 
} 

void printChar(void *c) 
{
    printf(" %c", *(char *)c);
}

int getCount(Node* head) 
{ 
    int count = 0;  // Initialize count 
    Node* current = head;  // Initialize current 
    while (current != NULL) 
    { 
        count++; 
        current = current->next; 
    } 
    return count; 
}

int popLast(Node* head) {
    currentElement = head;
    if (currentElement == NULL) {
        return (NULL);
    }

    while(currentElement->next != NULL) {
        currentElement = currentElement->next;
    }
    int res = currentElement->content;
    free(currentElement);
    return res;

}
