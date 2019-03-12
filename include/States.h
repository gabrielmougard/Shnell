/**
 * \file main.c
 * \author Gabriel Mougard
 * \brief States.h is basically an implementation of an HashMap ADT thought for storing
 * the states of the LEDs (value), with their associated <led_id> (key).
 */
#ifndef _STATES_
#define _STATES_

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0


/**
 * This helper structure is meant to store the <led_id> (the key)
 * associated with their states (true for 'on' and false for 'off')
 */

/**
 * \brief This structure describe the content of a hashMap node.
 */

typedef struct stateNode {
  pid_t pidKey;
  int key;
  bool state;
  struct stateNode *next;

} stateNode;


/**
 * \brief This structure describe the HashMap
 */
typedef struct stateTable {
  int size;
  stateNode **list;

} stateTable;

/**
 * This function create a new states map.
 *
 * \param int the size of the table.
 * \return stateTable
 */
stateTable *createTable(int size);

/**
 * Generates a hashcode for a specific key in the state table.
 *
 * \param stateTable* the pointed table
 * \param int the specified key
 *
 * \return int the hashcode
 */
int hashCode(stateTable *t, int key);

/**
 * Inserts content in the table.
 *
 * \param stateTable* the pointed table
 * \param int the key
 * \param bool the state
 *
 * \return void
 */
void insert(stateTable *t, int key, bool state, pid_t pid);

/**
 * Searchs for the specified key in the table.
 *
 * \param stateTable* the pointed table
 * \param int the specified key.
 *
 * \return int
 */
int lookup(stateTable *t, int key);

/**
 * print the content of the state table.
 *
 * \param stateTable* the pointed state table.
 * \return void
 */
void sumUp(stateTable *t);

/**
 * Recover the PID associated with the ID of the LED.
 *
 * \param stateTable* the pointed state table.
 * \param int the specified <led_id>
 * \return pid_t the associated PID.
 */
pid_t getPid(stateTable *t,int key);

#endif
