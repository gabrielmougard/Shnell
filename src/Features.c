#include "Features.h"
#include "States.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
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
};

static t_symstruct options[] = {
  {"No options",1}, {"No options",2}, {"specified directory (e.g : /home/gab/)",3},
  {"No options",4}, {"No options",5}, {"No options",6}, {"'on' or 'off' : choose the state and if not created, create it.\n'start-blink <delay>' or 'stop-blink <delay>' : start/stop blinking a led in a new terminal with delay between each blink.\n'status' : print the status of all the LEDs",7}
};

#define NKEYS (sizeof(lookupTable)/sizeof(t_symstruct))
#define NOPTIONS (sizeof(options)/sizeof(t_symstruct))

int keyFromString(t_symstruct **table,char *key) {
  int i;
  for (i = 0; i < NKEYS; i++) {
    t_symstruct *sym = table[i];
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

  char* buff; //store the key for retreiving options

  for (int i = 0; i < NOPTIONS; i++) {
    sprintf(buff,"%d",i);
    printf(" %s | options : %s\n", commands[i], keyFromString(options,buff));
  }

  printf("See the official documentation at : https://www.github.com/gabrielmougard/Shnell/doc.pdf\n");
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

    while ((myFile = readdir(directory)) != NULL) {

      if (args[1] == NULL) {

        sprintf(buf, "%s/%s", getenv("PWD"), myFile->d_name);
      }
      else {
        sprintf(buf, "%s/%s", args[1], myFile->d_name);
      }
      stat(buf, &mystat);
      printf("%zu",mystat.st_size);
      printf(" %s\n",myFile->d_name);

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
    if (!isdigit(array[i])) {
      return 0;
    }
  }
  return 1;
}


int shnell_led(char **args) {

  if (args[1] == NULL) {
    //error : missing arguments
    printf("\033[1;31m");
    printf("Error : missing arguments in the 'led' command. Use 'help' to see the documentation.\n");
    printf("\033[0m;");
    return 1;
  }

  //define 's' here
  int s;
  if (args[2] != NULL && isNumber(args[2])) {
    s = lookup(STATES,atoi(args[2]));
  }
  //

  switch(keyFromString(lookupTable,args[1])) {
    case A7: //on
      if (args[2] == NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : missing arguments in the 'led' command : <led_id>. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      if (args[3] != NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : too many arguments in the 'led' command. Use 'help' to see the documentation.\n");
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

      if ( s == -1) { // <led_id> do not exists

        insert(STATES,atoi(args[2]),1,NULL);
        printf("\033[1;33m"); //yellow color
        printf("The LED %s has been created and is on\n",args[2]);
        printf("\n");
      }
      else {
        //it exists, then check the state and if it's off, put it on. If it's already on, trigger the user and keep the same state
        if (lookup(STATES,atoi(args[2])) == 1) { //it was on
          printf("\033[1;33m"); //yellow color
          printf("The LED %s was already on\n",args[2]);
          printf("\n");
        }
        else { //it was off
          insert(STATES,atoi(args[2]),1,NULL);
          printf("\033[1;33m"); //yellow color
          printf("The LED %s has been switched on\n",args[2]);
          printf("\n");
        }
      }
      break;

    case A8: //off
      if (args[2] == NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : missing arguments in the 'led' command : <led_id>. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      if (args[3] != NULL) {
        //error : <led_id> not present
        printf("\033[1;31m");
        printf("Error : too many arguments in the 'led' command. Use 'help' to see the documentation.\n");
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
      if ( s == -1) { // <led_id> do not exists

        insert(STATES,atoi(args[2]),0,NULL);
        printf("\033[1;33m"); //yellow color
        printf("The LED %s has been created and is off\n",args[2]);
        printf("\n");
      }
      else {
        //it exists, then check the state and if it's off, put it on. If it's already on, trigger the user and keep the same state
        if (lookup(STATES,atoi(args[2])) == 1) { //it was on
          insert(STATES,atoi(args[2]),0,NULL);
          printf("\033[1;33m"); //yellow color
          printf("The LED %s has been switched off\n",args[2]);
          printf("\n");
        }
        else { //it was off
          printf("\033[1;33m"); //yellow color
          printf("The LED %s was already off\n",args[2]);
          printf("\n");
        }
      }
      break;

    case A9: //start-blink
      if(args[2] == NULL) {
        //error : missing argument
        printf("\033[1;31m");
        printf("Error : missing argument in the 'led start-blink' command : <led_id>. Use 'help' to see the documentation.\n");
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

      if(args[3] == NULL) {
        //error : missing argument
        printf("\033[1;31m");
        printf("Error : missing argument in the 'led start-blink' command : <delay>. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      if(!isNumber(args[3])) {
        //error : <delay> is not a number
        printf("\033[1;31m");
        printf("Error : <delay> must be an integer (in ms). Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      //check before if the led was created before starting forking process in xterm
      if(lookup(STATES,atoi(args[2])) == -1) {
        //error : LED not created
        printf("\033[1;31m");
        printf("Error : This led hasn't been created yet. Use 'led on <led_id>' to create one.\n");
        printf("\033[0m;");
        break;
      }
      else {
        //check the state. If the state is on, do the blinking. Else, print error.
        if(lookup(STATES,atoi(args[2])) == 0) { //led is off
          //error : LED not created
          printf("\033[1;31m");
          printf("Error : This led is off. Use 'led on <led_id>' to switch it on.\n");
          printf("\033[0m;");
          break;
        }
        else { //led is on, then do the blinking.

          //create pid
          pid_t pid = fork();

          //execute child process
          // pid is the first argument of our blink.out process
          // args[2] which is the <led_id> is the second argument.
          // args[3] which is the <delay> is the third argument.
          if (pid == 0) { //success in forking
            execl("/usr/bin/xterm","xterm","./blink.o",pid,args[2],args[3],NULL);

            //save pid to STATES
            insert(STATES,atoi(args[2]),1,pid);
          }
          else {
            //error : fork not successful
            printf("\033[1;31m");
            printf("Error : Blinking child process failed\n");
            printf("\033[0m;");
            break;
          }

        }

      }

    case A10: //stop-blink
      if(args[2] == NULL) {
        //error : missing argument
        printf("\033[1;31m");
        printf("Error : missing argument in the 'led stop-blink' command : <led_id>. Use 'help' to see the documentation.\n");
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

      if (lookup(STATES,atoi(args[2])) == -1) {
        //error : the <led_id> doesn't exists
        printf("\033[1;31m");
        printf("Error : The <led_id> doesn't exists.\n");
        printf("\033[0m;");
        break;
      }

      pid_t pidKey = getPid(STATES,atoi(args[2]));
      printf("\033[1;33m"); //yellow color
      printf("The LED %s has been stopped\n",args[2]);
      printf("\n");

      //kill effectively the process
      kill(pidKey,SIGKILL);
      break;

    case A11: //status

      if (args[2] != NULL) {
        //error : too many arguments
        printf("\033[1;31m");
        printf("Error : too many arguments in the 'led staus' command. Use 'help' to see the documentation.\n");
        printf("\033[0m;");
        break;
      }

      sumUp(STATES);


    case BADKEY:
      //error : wrong argument
      printf("\033[1;31m");
      printf("Error : wrong arguments in the 'led' command. Use 'help' to see the documentation.\n");
      printf("\033[0m;");
      break;

  }
  return 1;
}
