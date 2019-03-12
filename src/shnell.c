/**
 * \file main.c
 * \author Gabriel Mougard
 * \brief main file
 */

#include "Node.h"
#include "States.h"
#include "Shared.h"
#include "Features.h"

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

#define DELIM " \t\r\a\n"

int main(int argc, char **argv) {

    //for the sake of beauty even in the poor graphical environment of the terminal !
    printBanner();

    initializeStates();
    //launch the shell loop with the specified configuration
    launchShell();

    //exit with success
    return EXIT_SUCCESS;
}

/**
 * readCommand reads a line from stdin
 *
 * \param void
 * \return Node* return the entered data in a LinkedList, thus we don't need a buffer and we have a dynamic storage.
 */
Node *readCommand(void) {
    Node *start = NULL;
    unsigned char_size = sizeof(char);
    char current_c;
    Node *previous_c = NULL;

    while(true) {
        //read the character
        current_c = getchar();


        if(current_c == '\n') {
            push(&start,&current_c,char_size);
            return start;
        }
        else {
            if (current_c == '\\') {

                while(current_c != '\n') {
                    current_c = getchar();

                    //only push in previous_c
                    if (current_c != ' ') {
                        push(&previous_c,&current_c,char_size);
                    }
                }
                if(getCount(&previous_c) > 0) {
                    //error case
                    fprintf(stderr, "Shnell: multiple lines error\n");
                    exit(EXIT_FAILURE);
                }
                else {
                    printf("\033[1;33m"); //yellow color
                    printf("... ");
                    printf("\033[0m;");
                }

            }
            else {
                //register the character
                push(&start,&current_c,char_size);
            }
        }
    }
}

/**
 * Parses the entered command.
 *
 * \param Node* the entered command.
 * \return char** a list of arguments.
 */
char **readArgs(Node *command) {
    char* convertedCommand = linkedListToArray(command);
    int nbElements = sizeof(convertedCommand)/sizeof(convertedCommand[0]);
    int index = 0;
    char **words = malloc(nbElements*sizeof(char*));
    char *word;

    word = strtok(command,DELIM);
    while(word != NULL) {
        words[index] = word;
        index++;
        word = strtok(NULL,DELIM);
    }
    words[index] = NULL;
    return words;
}

/**
 * launchShell initialize the process of reading the current line, then call the line parser
 * and finally execute the command while checking the exited variable to see if the program must end.
 *
 * \param void
 * \return void
 */
void launchShell(void) {
    Node* command;
    char** args;

    bool exited = false;

    while(!exited) {
        printf("\033[1;31m");
        printf(">>> ");
        printf("\033[0m;");

        command = readCommand();
        args = readArgs(command);
        exited = executeCommand(args);

        free(command);
        free(args);
    }
}

/**
 * Launch the shell process
 *
 * \param char** the arguments of the command
 * \return int
 */
int shnellLaunch(char **args) {
    pid_t pid,waitPid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0],args) == -1) {
            perror("shnell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        //forking error
        perror("shnell");
    }
    else {
        //parent process
        do {
            waitPid = waitpid(pid,&status,WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * Execute the entered command and calls the right builtin feature function.
 *
 * \param char** the arguments of the command
 * \return int
 */
int executeCommand(char **args) {
    if (args[0] == NULL) {
        //empty command
        return 1;
    }

    for (int i = 0; i < builtinLength(); i++) {
        if (strcmp(args[0],commands[i]) == 0) {
            return (*builtin_features[i])(args);
        }
    }

    return shnellLaunch(args);

}

/**
 * Print a beautiful banner !
 * \param void
 * \return void
 */
void printBanner(void) {
    printf("\tA Shell Snips Challenge by Gabriel Mougard.\n");

    char ch, file_name[25];
	FILE *fp;

	fp = fopen("banner","r"); //this file will be pasted in the same directory of the binaries

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	printf("\n");
	while((ch = fgetc(fp)) != EOF) {
		printf("%c",ch);
	}
  printf("\n");
	fclose(fp);

}

void initializeStates(void) {
  stateTable *STATES = createTable(50);
}
