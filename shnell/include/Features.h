/**
 * \file main.c
 * \author Gabriel Mougard
 * \brief Features.h groups builtin features (commands) available in the shell.
 */

#ifndef _FEATURES_
#define _FEATURES_

#include <stdio.h>
#include <stdlib.h>


/**
 * The list of built-in commands of Shnell
 */

/**
 * This command prints a documentation
 *
 * \param char** command arguments
 * \return void
 */
int shnell_help(char **args);

/**
 * This command change the current directory
 *
 * \param char** command arguments
 * \return void
 */
int shnell_cd(char **args);

/**
 * This command prints the content of a folder and their sizes
 *
 * \param char** command arguments
 */
int shnell_ls(char **args);

/**
 * This command prints the working directory
 *
 * \param char** command arguments
 * \return void
 */
int shnell_pwd(char **args);

/**
 * This command ends the program
 *
 * \param char** command arguments
 */
int shnell_exit(char **args);

/**
 * This command prints the version of the program
 *
 * \param char** command arguments
 * \return void
 */
int shnell_version(char **args);

/**
 * This command allows different processes concerning the LEDs management,
 * which is the creation, deletion, status, and blinking routines.
 *
 * \param char** command arguments
 * \return void
 */
int shnell_led(char **args);


#endif
