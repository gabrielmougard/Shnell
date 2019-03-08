#include "Features.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define VERSION "1.0"

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
