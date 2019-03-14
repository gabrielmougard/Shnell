#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "LinkedList.h"

#define VERSION "0.1"
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

//helper functions
int keyFromString(t_symstruct **table,char *key) {
  
  int i;
  for (i = 0; i < NKEYS; i++) {
    printf("I am in the keys..");
    t_symstruct *sym = table[i];
    if (strcmp(sym->key,key) == 0)
      return sym->val;
  }
  return BADKEY;
}

//

/*
  builtin shell commands:
 */
int shnell_cd(char **args, struct Node* head);
int shnell_help(char **args, struct Node* head);
int shnell_exit(char **args, struct Node* head);
int shnell_version(char **args, struct Node* head);
int shnell_pwd(char **args, struct Node* head);
int shnell_led(char **args, struct Node* head);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "version",
  "pwd",
  "led"
};

int (*builtin_func[]) (char **,struct Node* head) = {
  &shnell_cd,
  &shnell_help,
  &shnell_exit,
  &shnell_version,
  &shnell_pwd,
  &shnell_led
};

int shnell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int shnell_cd(char **args,struct Node* head)
{
  if (args[1] == NULL) {
    fprintf(stderr, "shnell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("shnell");
    }
  }
  return 1;
}

int shnell_version(char **args, struct Node* head) {

  if (args[1] != NULL) {
    //error : there's something after the 'version' command
    printf("\033[1;31m");
    printf("Error : there is no options after 'version' command.\n");
    printf("\033[0m");
    return 1; // don't escape but run on an other line
  }

  printf("\033[1;33m"); //yellow color
  printf("Current version : %s\n",VERSION);
  printf("\033[0m");

  return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int shnell_help(char **args, struct Node* head)
{
  int i;
  printf("\033[1;33m"); //yellow color
  printf("Shnell : HELP\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < shnell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  printf("\033[0m");
  return 1;
}

int shnell_pwd(char **args, struct Node* head) {

  if (args[1] != NULL) {
    //error : there's something after the 'pwd' command
    printf("\033[1;31m");
    printf("Error : there is no options after 'pwd' command.\n");
    printf("\033[0m");
    return 1; // don't escape but run on an other line
  }

  printf("\tWorking directory : %s\n",getenv("PWD"));
  printf("\tFilepath : %s/%s\n",getenv("PWD"),__FILE__);
  return 1;
}


/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int shnell_exit(char **args,struct Node* head)
{
  return 0;
}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int shnell_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("shnell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("shnell");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int shnell_led(char **args, struct Node* head) {
  
  char* arg1 = args[1];
  char* arg2 = args[2];
  char* arg3 = args[3];

  if (arg1 == NULL) {
    //error : missing arguments
    printf("\033[1;31m");
    printf("Error : missing arguments in the 'led' command. Use 'help' to see the documentation.\n");
    printf("\033[0m");
    return 1;
  }
  
  //define 's' here
  int s = 0;
  if (arg2 != NULL && atoi(arg2) != 0) {

    //s = lookup(atoi(arg2));
    s = getState(head,atoi(arg2));
    
  } else {
    if (strcmp(arg1,"status") == 0) {
      sumUp(head);
      return 1;
    }
    else {
      printf("\033[1;31m");
      printf("Error : wrong argument or lacking <LED_ID>. Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }
  }

  // at this point arg2 is not NULL and is an integer number

  if(strcmp(arg1,"on") == 0) {
    
      if (arg3 != NULL) {
        //error : too many arguments
        printf("\033[1;31m");
        printf("Error : too many arguments in the 'led on' command. Use 'help' to see the documentation.\n");
        printf("\033[0m");
        return 1;
      }

      //check if it already exists. If not, create it.

      if ( s == -1) { // <led_id> do not exists

        //insert(atoi(arg2),-1,1);
        append(&head,atoi(arg2),-1,1);
        printf("\033[1;33m"); //yellow color
        printf("The LED #%s has been created and is on\n",arg2);
        printf("\033[0m");
        return 1;
      }
      else {
        //it exists, then check the state and if it's off, put it on. If it's already on, trigger the user and keep the same state
        if (getState(head,atoi(arg2)) == 1) { //it was on
          printf("\033[1;33m"); //yellow color
          printf("The LED #%s was already on\n",arg2);
          printf("\033[0m");
          printf("\n");
          return 1;
        }
        else { //it was off
          append(&head,atoi(arg2),-1,1);
          printf("\033[1;33m"); //yellow color
          printf("The LED #%s has been switched on\n",arg2);
          printf("\033[0m");
          printf("\n");
          return 1;
        }
      }
      
  }
  else if(strcmp(arg1,"off") == 0) {
      
    if (arg3 != NULL) {
      //error : too many arguments
      printf("\033[1;31m");
      printf("Error : too many arguments in the 'led off' command. Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    if(atoi(arg2) == 0) {
      //error : <led_id> is not a number
      printf("\033[1;31m");
      printf("Error : <led_id> must be an integer. Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    //check if it already exists. If not, create it.
    if ( s == -1) { // <led_id> do not exists

      append(&head,atoi(arg2),-1,0);
      printf("\033[1;33m"); //yellow color
      printf("The LED #%s has been created and is off\n",arg2);
      printf("\033[0m");
      printf("\n");
      return 1;
    }
    else {
      //it exists, then check the state and if it's off, put it on. If it's already on, trigger the user and keep the same state
      if(getState(head,atoi(arg2)) == 1) { //it was on
        append(&head,atoi(arg2),-1,0);
        printf("\033[1;33m"); //yellow color
        printf("The LED #%s has been switched off\n",arg2);
        printf("\033[0m");
        printf("\n");
        return 1;
      }
      else { //it was off
        printf("\033[1;33m"); //yellow color
        printf("The LED #%s was already off\n",arg2);
        printf("\033[0m");
        printf("\n");
        return 1;
      }
    }  
  }
  else if(strcmp(arg1,"start-blink") == 0) { //start-blink
      
    if(atoi(arg2) == 0) {
      //error : <led_id> is not a number
      printf("\033[1;31m");
      printf("Error : <led_id> must be an integer. Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    if(arg3 == NULL) {
      //error : <delay> is not precised
      printf("\033[1;31m");
      printf("Error : <delay> must be specified (in ms). Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    if(atoi(arg3) == 0) {
      //error : <delay> is not a number
      printf("\033[1;31m");
      printf("Error : <delay> must be an integer (in ms). Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    //check before if the led was created before starting forking process in xterm
    if(getState(head,atoi(arg2)) == -1) {
      //error : LED not created
      printf("\033[1;31m");
      printf("Error : This led hasn't been created yet. Use 'led on <led_id>' to create one.\n");
      printf("\033[0m");
      return 1;
    }
    else {
      //check the state. If the state is on, do the blinking. Else, print error.
      if(getState(head,atoi(arg2)) == 0) { //led is off
        //error : LED not created
        printf("\033[1;31m");
        printf("Error : This led is off. Use 'led on <led_id>' to switch it on.\n");
        printf("\033[0m");
        return 1;
      }
      else { //led is on, then do the blinking.

        //create pid
        pid_t pid = fork();

        //execute child process
        // pid is the first argument of our blink.out process
        // args[2] which is the <led_id> is the second argument.
        // args[3] which is the <delay> is the third argument.
        if (pid == 0) { //success in forking
          execl("/usr/bin/xterm","xterm","blink",pid,arg2,arg3,NULL); //blink is the name of the command since it will be pasted in /usr/local/bin

          //save pid to STATES
          append(&head,atoi(arg2),pid,1);
        }
        else {
          //error : fork not successful
          printf("\033[1;31m");
          printf("Error : Blinking child process failed\n");
          printf("\033[0m");
          return 1;
        }
      }
    }
  }
  else if (strcmp(arg1,"stop-blink") == 0) { //stop-blink
      
    if(atoi(arg2) == 0) {
      //error : <led_id> is not a number
      printf("\033[1;31m");
      printf("Error : <led_id> must be an integer. Use 'help' to see the documentation.\n");
      printf("\033[0m");
      return 1;
    }

    if (getState(head,atoi(arg2)) == -1) {
      //error : the <led_id> doesn't exists
      printf("\033[1;31m");
      printf("Error : The <led_id> doesn't exists.\n");
      printf("\033[0m");
      return 1;
    }

    pid_t pidKey = getPid(head,atoi(arg2));
    printf("\033[1;33m"); //yellow color
    printf("The LED %s has been stopped\n",arg2);
    printf("\033[0m");
    printf("\n");

    //kill effectively the process
    kill(pidKey,SIGKILL);
    return 1;
  }

  else {
    //error : wrong argument
    printf("\033[1;31m");
    printf("Error : wrong arguments in the 'led' command. Use 'help' to see the documentation.\n");
    printf("\033[0m");
    return 1;
  }
  
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int shnell_execute(char **args, struct Node* head)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < shnell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args,head);
    }
  }

  return shnell_launch(args);
}

#define SHNELL_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *shnell_read_line(void)
{
  int bufsize = SHNELL_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "shnell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += SHNELL_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "shnell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define SHNELL_TOK_BUFSIZE 64
#define SHNELL_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **shnell_split_line(char *line)
{
  int bufsize = SHNELL_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "shnell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, SHNELL_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += SHNELL_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "shnell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SHNELL_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void shnell_loop(struct Node* head)
{
  char *line;
  char **args;
  int status;

  do {
    printf("\033[1;31m");
    printf(">>> ");
    printf("\033[0m");
    line = shnell_read_line();
    args = shnell_split_line(line);
    status = shnell_execute(args,head);

    free(line);
    free(args);
  } while (status);
}

/**
 * Print a beautiful banner !
 * @param void
 * @return void
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

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  //create the ADT which will contains the ledId,pid,state of the LEDs
  struct Node head;

  //print banner
  printBanner();

  // Run command loop.
  shnell_loop(&head);

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
