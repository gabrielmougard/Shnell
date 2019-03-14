#include "LinkedList.h"

#include <stdlib.h>
#include <stdio.h>

void append(struct Node** head_ref,int ledId,int pid, int state) {
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->ledId  = ledId;
    new_node->pid  = pid;
    new_node->state  = state;

  
    /* 3. This new node is going to be the last node, so make next of 
          it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) {

        if (last->ledId == ledId) { //if the specified ledId is already present, modify the present node
            //modify the pid and the state
            last->pid = pid;
            last->state = state;
            return;
        }

        last = last->next; 
    }
    /* 6. Change the next of last node */
    last->next = new_node; 
    return; 
}

void sumUp(struct Node* head) {

    struct Node* last = head;

    if (last == NULL) {
       printf("<LED_ID>\t<PID>\t<STATE>\n");  
    }
    while (last != NULL) 
    { 
        printf("<LED_ID> : %d\t<PID> : %d\t<STATE> : %d\n", last->ledId, last->pid, last->state); 
        last = last->next; 
    } 
}

int getPid(struct Node* head, int ledId) {
    struct Node* current = head;  // Initialize current 
    while (current != NULL) 
    { 
        if (current->ledId == ledId) 
            return current->pid; 
        current = current->next; 
    } 
    return -1; 
}

int getState(struct Node* head, int ledId) {
    struct Node* current = head;  // Initialize current 
        while (current != NULL) 
        { 
            if (current->ledId == ledId) 
                return current->state; 
            current = current->next; 
        } 
        return -1;
}
