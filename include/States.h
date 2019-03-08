#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0


/**
 * This helper structure is meant to store the <led_id> (the key)
 * associated with their states (true for 'on' and false for 'off')
 */


typedef struct stateNode {
  int key;
  bool state;
  stateNode *next;

} stateNode;

typedef struct stateTable {
  int size;
  stateNode **list;

} stateTable;

stateTable *createTable(int size);

int hashCode(stateTable *t, int key);

void insert(stateTable *t, int key, bool state);

int lookup(stateTable *t, int key);
