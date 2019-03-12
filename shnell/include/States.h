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

/**
 * Inserts content in the table.
 *
 * \param stateTable* the pointed table
 * \param int the key
 * \param bool the state
 *
 * \return void
 */
void insert(int ledID, int pid, int state);

/**
 * Searchs for the specified key in the table.
 *
 * \param stateTable* the pointed table
 * \param int the specified key.
 *
 * \return int
 */
int lookup(int ledID);

/**
 * print the content of the state table.
 *
 * \param stateTable* the pointed state table.
 * \return void
 */
void sumUp(void);

/**
 * Recover the PID associated with the ID of the LED.
 *
 * \param stateTable* the pointed state table.
 * \param int the specified <led_id>
 * \return pid_t the associated PID.
 */
int getPid(int ledID);

#endif
