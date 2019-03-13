#include "States.h"

#include <stdio.h>
#include <stdlib.h>

int lookup(int ledID) {

	FILE *fp;
	char str[200];
	char *filename = "states.dat";
	char delim[] =" \t";

	fp = fopen(filename,"r");
	if (fp == NULL) {
		printf("could not open file %s",filename);
		return 1;
	}

	while(fgets(str,200,fp) != NULL) {
		
		char *ptr =strtok(str,delim);
		if (atoi(ptr) == ledID) {
			ptr = strtok(NULL,delim);
			ptr = strtok(NULL,delim);
			return atoi(ptr);
		}
		
	}
	
	fclose(fp);
	return -1; //return -1 because hasn't been found   ==> this if the lookup function
}

void insert(int key, int pid, int state) {
	
	FILE *fp;
	FILE *tempFile;

	char str[200];
	char delim[] =" \t";
	int lineCount = 0;
	int temp = 1;

	if(lookup(key) == -1) {
		fp = fopen("states.dat","a");
	}
	else {
		fp = fopen("states.dat","r");
		tempFile = fopen("statesTemp.dat","w");
	}
	
	//check if key already here
	while(fgets(str,200,fp) != NULL) {
		lineCount++;
		
		char *ptr =strtok(str,delim);
		if (atoi(ptr) == key) {
			
			//key already here so modify the pid and the state
			rewind(fp);
			char ch = 'A';
			while(ch != EOF) {
				ch = getc(fp);
				if(temp != lineCount) {
					putc(ch,tempFile);
				}
				if (ch == '\n') {
					temp++;
				}

			}

			//then add the content at the end of temp file and rename it
			fprintf(tempFile,"%d\t%d\t%d\n",key,pid,state);
			fclose(fp);
			fclose(tempFile);
			remove("states.dat");
			rename("statesTemp.dat","states.dat");
			return;

		}
		
	}

	fprintf(fp,"%d\t%d\t%d\n",key,pid,state);
	fclose(fp);
}

void sumUp(void) {
	printf("<LED_ID>\t<PID>\t<STATE>\n");
	FILE *fp;
	char str[200];
	char delim[] ="\t";
	fp = fopen("states.dat","r");

	
	while(fgets(str,200,fp) != NULL) {
		char *ptr =strtok(str,delim);
		printf("<LED_ID> : %s\t",ptr);
		ptr =strtok(NULL,delim);
		printf("<PID> : %s\t",ptr);
		ptr =strtok(NULL,delim);
		printf("<STATE> : %s\n",ptr);
	}
}

int getPid(int ledID) {
	FILE *fp;
	char str[200];
	char *filename = "states.dat";
	char delim[] =" \t";

	fp = fopen(filename,"r");
	if (fp == NULL) {
		printf("could not open file %s",filename);
		return 1;
	}

	while(fgets(str,200,fp) != NULL) {
		
		char *ptr =strtok(str,delim);
		if (atoi(ptr) == ledID) {
			ptr = strtok(NULL,delim);
			return atoi(ptr);
		}
		
	}
	
	fclose(fp);
	return -1; //return -1 because hasn't been found
}
