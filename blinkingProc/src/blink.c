#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char* one = "one"; //this file will be pasted into the same folder of binary
    char* zero = "zero"; //this file will be pasted into the same folder of binary

    int delay = atoi(argv[3]);//recover the parameter of delay
    int pid = atoi(argv[2]);//recover the PID
    int led_id = atoi(argv[1]);//recover the <led_id>

    while(1) {
      usleep(1000*delay); //milliseconds conversion
      printLetter(one,pid,led_id);
      fflush(stdout);
      usleep(1000*delay);
      printLetter(zero,pid,led_id);
    }
    
    return 0;
}

void printLetter(char* filename, int pid, int led_id) {

  char ch, file_name[25];
	FILE *fp;

	fp = fopen(filename,"r");

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	printf("\n");
  printf("LED ID : %d\tPID : %d\n",led_id,pid);
	while((ch = fgetc(fp)) != EOF) {
		printf("%c",ch);
	}

	fclose(fp);

}
