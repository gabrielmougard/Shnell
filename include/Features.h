
/**
 * The list of built-in commands of Shnell
 */

int shnell_help(char **args);
int shnell_cd(char **args);
int shnell_ls(char **args);
int shnell_pwd(char **args);
int shnell_exit(char **args);
int shnell_version(char **args);
int shnell_led(char **args);

int builtinLength(void);
