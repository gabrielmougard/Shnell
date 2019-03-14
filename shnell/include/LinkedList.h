#ifndef _LINKEDLIST_
#define _LINKEDLIST_

struct Node  
{ 
  int ledId;
  int pid;
  int state; 
  struct Node *next; 
}; 

void append(struct Node** head_ref,int ledId,int pid, int state);
void sumUp(struct Node* head);
int getPid(struct Node* head, int ledId);
int getState(struct Node* head, int ledId);

#endif