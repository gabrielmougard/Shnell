#include "States.h"

#include <stdio.h>
#include <stdlib.h>

stateTable *createTable(int size) {
  stateTable *t = (stateTable*)malloc(sizeof(stateTable));
  t->size = size;
  t->list = (stateNode**)malloc(sizeof(stateNode*)*size);
  for (int i = 0; i < size; i++) {
    t->list[i] = NULL;
  }
  return t;
}

int hashCode(stateTable *t, int key) {
  if (key < 0) {
    return -(key%t->size);
  }
  return key%t->size;
}

void insert(stateTable *t, int key, bool state) {
  int pos = hashCode(t,key);
  stateNode *list = t->list[pos];
  stateNode *newNode = (stateNode*)malloc(sizeof(stateNode));
  stateNode *temp = list;
  while(temp) {
    if (temp->key == key) {
      temp->state = state;
      return;
    }
    temp = temp->next;
  }
  newNode->key = key;
  newNode->state = state;
  newNode->next = list;
  t->list[pos] = newNode;
}

int lookup(stateTable *t, int key) {
  int pos = hashCode(t,key);
  stateNode *list = t->list[pos];
  stateNode *temp = list;
  while(temp) {
    if(temp->key == key) {
      return temp->state;
    }
    temp = temp->next;
  }
  return -1;
}

void sumUp(stateTable *t) {
  stateNode *list = t->list[0];
  
  while(list) {
    printf("<led_id> : %d\t<state> : %d\n",list->key, list->state);
  }
}
