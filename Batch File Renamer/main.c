#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER_SIZE 101
#define FILE_LOCATION "/media/dante_g/Lexar/Audio\ Recordings/"

void read_in_names();
void convert_file_spaces();
void rename_files(char *current[], char *new[]);

int noOfEntries = 0;
char tempFile[] = "dataXXXXXX";

int main(int argc, char *argv[]) {
	
	/* CreateS a temporary file */
	int fp = mkstemp(tempFile);
	if(fp == -1) {
		perror("Failed to create temporary file");
		exit(-1);
	}
	close(fp);
	
	/* Converts file names to ones that can be used in commands */
	convert_file_spaces();

	/* Reads in the names to be changed to & calls rename function */
	read_in_names();

	unlink(tempFile);
	return 0;
}

void convert_file_spaces() {

	char append[] = "\ ";
	char *buffer;
	buffer = calloc(100, sizeof(char));

	FILE *wFile = fopen(tempFile, "w");	
	FILE *file = popen("cd /media/dante_g/Lexar/Audio\\ Recordings && ls | grep .wav", "r");
	
	char *temp2,*ptr;
	char temp[BUFFER_SIZE]; 
	temp[100] = '\0';

	while(fgets(temp, BUFFER_SIZE, file) != NULL) {

		char *newName = calloc(BUFFER_SIZE, sizeof(char));
		newName[100] = '\0';
		
		/* Breaking down using strtok() */
		temp2 = strtok(temp, " ");

		while(temp2 != NULL) {

			strcat(newName, temp2);

			if(!strchr(newName, '\n'))
				strcat(newName, append);

			temp2 = (strtok(NULL, " "));
		}

		noOfEntries++;
		fprintf(wFile, "%s", newName);
	}
	free(buffer);
	fclose(file);
	fclose(wFile);
}

void read_in_names() {

	char *ptr;
	
	/* Setting up array of strings */
	char *curName[noOfEntries];
	char *newName[noOfEntries];

	for(int i = 0; i < noOfEntries; i++) {
		curName[i] = calloc(sizeof(char),BUFFER_SIZE);
		newName[i] = calloc(sizeof(char),BUFFER_SIZE);
	}

	/* Reading in new names */
	FILE *newNameFile = fopen("/home/dante_g/Desktop/fileReader/listofnames.txt", "r");
	for(int i = 0; (i < noOfEntries) && (fgets(newName[i], BUFFER_SIZE, newNameFile) != NULL); i++) {
		if((ptr = strchr(newName[i], '\n')))
			*ptr = '\0';
	}
	fclose(newNameFile);

	/* Reading in old names*/
	FILE *oldNameFile = fopen(tempFile, "r");
	for(int i = 0; (i < noOfEntries) && (fgets(curName[i], BUFFER_SIZE, oldNameFile) != NULL); i++) {
		if((ptr = strchr(curName[i], '\n')))
			*ptr = '\0';
	}
	fclose(oldNameFile);

	rename_files(curName, newName);		
}

void rename_files(char *current[], char *new[]) {

	for(int i = 0; (i < noOfEntries) && (current[i] != NULL && new[i] != NULL); i++) {
		
		if(fork() == 0) {
			char tempc[200] = FILE_LOCATION;
			strcat(tempc, current[i]);

			char tempn[200] = FILE_LOCATION;
			strcat(tempn, new[i]);

			execl("/bin/mv", "/bin/mv", tempc, tempn, NULL);

			perror("Error executing the command");
			exit(1);
		}
	}

	pid_t id;
	while((id = waitpid(-1, NULL, 0))) {
		if(errno == ECHILD) //If a child does not exist 
			break;
	}

}