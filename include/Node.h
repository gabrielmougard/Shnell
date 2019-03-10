/**
 * \file main.c
 * \author Gabriel Mougard
 * \brief Node.h is a way to store generic things with a dynamic storage.
 * Indeed, we do not want to have a limited buffer size when entering a command.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *content;
    Node *next;
} Node;

/**
 * This function add a node at the beginning of the LinkedList.
 * fptr is is used to access the function to be used for printing current node data.
 *
 * \param Node head reference
 * \param void new data to be added
 * \param size_t size of the data to be added
 * \return void
 */
void push(Node** headRef, int *newContent, size_t contentSize);

/**
 * This function prints the LinkedList
 *
 * \param Node the starting node
 * \return void
 */
void linkedListToArray(Node *node);

/**
 * This function prints an integer
 *
 * \param genericType
 * \return void
 */
void printInteger(void *i);

/**
 * Get the length of a generic LinkedList
 *
 * \param Node head node
 * \return int
 */
int getCount(Node* head);

/**
 * This function returns the last element of the LinkedList ans delete it.
 *
 * \param Node* head node
 * \return int since content of a node is int
 */
int popLast(Node* head);
