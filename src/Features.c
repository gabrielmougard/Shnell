#include "Features.h"
#include "States.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define VERSION "1.0"

#define BADKEY -1
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define A8 8
#define A9 9
#define A10 10
#define A11 11

/**
 * The list of the available commands (the options are not listed here)
 */
char *commands[] = {
  "help",
  "version",
  "cd",
  "pwd",
  "ls",
  "exit",
  "led"
};

typedef struct { char *key; int val;} t_symstruct;

/**
 * Structure which contains the many options of the commands in the respective
 * order (see above).
 */
static t_symstruct lookupTable[] = {
  {"No options",A1}, {"No options",A2}, {"specified directory (e.g : /home/gab/)",A3},
  {"No options",A4}, {"No options",A5}, {"No options",A6}, {"on",A7}, {"off",A8}, {"start-blink",A9},
  {"stop-blink",A10}, {"status",A11}
}

#define NKEYS (sizeof(lookupTable)/sizeof(t_symstruct))

int keyFromString(char *key) {
  int i;
  for (i = 0; i < NKEYS; i++) {
    t_symstruct *sym = lookupTable[i];
    if (strcmp(sym->key,key) == 0)
      return sym->val;
  }
  return BADKEY;
}

int (*builtin_features[])(char **) = {
  &shnell_help,
  &shnell_version,
  &shnell_pwd,
  &shnell_ls,
  &shnell_cd,
  &shnell_exit,
  &shnell_led
};

int builtinLength() {
  return sizeof(commands)/sizeof(char *);
}

/**
 * 'help' command implementation
 *
 * @param char**
 * @return int
 */
int shnell_help(char **args) {

  if (args[1] != NULL) {
    //error : there's something after the 'help' command
    printf("\033[1;31m");
    printf("Error : there is no options after 'help' command.\n");
    printf("\033[0m;");
    return 1; // don't escape but run on an other line
  }

  printf("\033[1;33m"); //yellow color
  printf("Hi ! You need help ? Here are the available built-in commands :\n");
  printf("\n");

  for (int i = 0; i < builtinLength(); i++) {
    printf(" %s | options : %s\n", commands[i], command_options[i]);
  }

  printf("See the official documentation at : https://www.github.com/gabrielmougard/Shnell/doc.pdf\n", );
  printf("\033[0m;");
  return 1;
}

int shnell_version(char **args) {

  if (args[1] != NULL) {
    //error : there's something after the 'version' command
    printf("\033[1;31m");
    printf("Error : there is no options after 'version' command.\n");
    printf("\033[0m;");
    return 1; // don't escape but run on an other line
  }
  printf("\033[1;33m"); //yellow color
  printf("Current version : %s\n",VERSION);
  printf("\033[0m;");

  return 1;
}

int shnell_pwd(char **args) {

  if (args[1] != NULL) {
    //error : there's something after the 'version' command
    printf("\033[1;31m");
    printf("Error : there is no options after 'pwd' command.\n");
    printf("\033[0m;");
    return 1; // don't escape but run on an other line
  }

  printf("\tWorking directory : %s\n",getenv("PWD"));
  printf("\tFilepath : %s/%s\n",getenv("PWD"),__FILE__);
  return 1;
}

int shnell_ls(char **args) {
    DIR *directory;
    struct dirent *myFile;
    struct stat mystat;

    char buf[512];
    if (args[1] == NULL) {
      //the command is just 'ls'
      directory = opendir(getenv("PWD"));
    }
    else {
      directory = opendir(args[1]);
    }

    if (args[2] != NULL) {
      //error : too many arguments
      printf("\033[1;31m");
      printf("Error : too many arguments in the 'ls' command. Type 'help' to show the available options.\n");
      printf("\033[0m;");
      return 1;
    }

    while ((myfile = readdir(directory)) != NULL) {

      if (args[1] == NULL) {

        sprintf(buf, "%s/%s", getenv("PWD"), myfile->d_name);
      }
      else {
        sprintf(buf, "%s/%s", args[1], myfile->d_name);
      }
      stat(buf, &mystat);
      printf("%zu",mystat.st_size);
      printf(" %s\n",myfile->d_name);

    }
    closedir(directory);
    return 1;
}

int shnell_exit(char **args) {
  if (args[1] != NULL) {
    //error : too many arguments
    printf("\033[1;31m");
    printf("Error : too many arguments in the 'exit' command. Did you mean 'exit'?\n");
    printf("\033[0m;");
    return 1;
  }

  printf("OK ! Good Bye !\n");
  return 0;
}

int shnell_cd(char **args) {
  //TODO

  
}

int isNumber(char *array) {

  int size = sizeof(array)/sizeof(char);
  for (int i = 0; i < size; i++) {
    if (isalpha(array[i])) {
      return 0;
    }
  }
  return 1;
}


int shnell_led(char **args) {
  //TODO
  if (args[1] == NULL) {
    //error : missing arguments
    printf("\033[1;31m");
    printf("Error : missing arguments in the 'led' command. Use 'help' to see the documentation.\n");
    printf("\033[0m;");
    return 1;
  }

  switch(keyFromString(args[1])) {
    case A7: //on
      if (args[2] == NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : missing arguments in the 'led' command : <led_id>. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      if(!isNumber(args[2])) {
        //error : <led_id> is not a number
        printf("\033[1;31m");
        printf("Error : <led_id> must be an integer. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      //check if it already exists. If not, create it.
      if (!ledIdExists(args[2])) {

      }
      else {
        //it exists, then check the state and if it's off, put it on. If it's already on, trigger the user and keep the same state

      }


    case A8: //off
      if (args[2] == NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : missing arguments in the 'led' command : <led_id>. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

    case A9: //start-blink

    case A10: //stop-blink

    case A11: //status

    case BADKEY:
      //error : wrong argument
      printf("\033[1;31m");
      printf("Error : wrong arguments in the 'led' command. Use 'help' to see the documentation.\n");
      printf("\033[0m;");
      break;

  }
  return 1;
}
