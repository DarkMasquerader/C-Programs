/*
This is the 2nd version of my coursework deadline script.
This version (in addition to ver1) prints the due time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define PARAMETERS 4
#define BUFFER_SIZE 51

/* Date Variables */
char day[10], month[10], date[10], currTime[10], timeZone[10], year[10];

int get_month_number();
int get_days_in_month();
int get_number_of_lines();

void parse_date();
void int_to_string(int number, char dueDate[]);
void calc_days_left(char *dueDate[], int noOfLines);
void parse_file(char *name[], char *assignment[], char *due[], char *time[]);
void print_results(char *name[], char *assignment[], char *due[], char *time[], int noOfLines);

char id_digit(int digit);

/* Does Not Handle Leap Years */
/* Works for maximum 11 months - Year is not factored in */
int main(void) {

	/* File Column Variables */
	int noOfLines = get_number_of_lines();
	char *courseName[noOfLines];
	char *assignmentName[noOfLines];
	char *dueDate[noOfLines];
	char *dueTime[noOfLines];

	for(int i = 0; i < noOfLines; i++) {
		courseName[i] = malloc(sizeof(char) * BUFFER_SIZE);
		assignmentName[i] = malloc(sizeof(char) * BUFFER_SIZE);
		dueDate[i] = malloc(sizeof(char) * BUFFER_SIZE);
		dueTime[i] = malloc(sizeof(char) * BUFFER_SIZE);
	}

	/* Loading in today's date */
	parse_date();

	/* Loading in the file */
	parse_file(courseName, assignmentName, dueDate, dueTime);

	/* Calculates the remaining days */
	calc_days_left(dueDate, noOfLines);

	/* Organises into order of due date */

	/* Prints Calculations */
	print_results(courseName, assignmentName, dueDate, dueTime, noOfLines);

	return 0;
}


void calc_days_left(char *dueDate[], int noOfLines) {

	char *localDay, *localMonth;
	char *listOfMonths[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
							"Oct", "Nov", "Dec"};

	for(int i = 0; i < noOfLines; i++) {
		if(!strcmp(dueDate[i], " "))
			break;

		localDay = strtok(dueDate[i], "/");
		localMonth = strtok(NULL, "/");


		int monthDifference = (atoi(localMonth) - get_month_number()); 
		int dateDifference = (atoi(localDay) -atoi(date));

		/* Custom date - 15/3
			
			int monthDifference = (atoi(localMonth) - 3); 
			int dateDifference = (atoi(localDay) -atoi(date));

		*/

		//printf("Month Difference: %d\nDate Difference: %d\n", monthDifference, dateDifference);

		if((monthDifference == 0 && dateDifference < 0) | (monthDifference < 0)) //Previous month, or day in month
			dueDate[i] = "Passed";
		else if (monthDifference == 0 && dateDifference == 0) //Today
			dueDate[i] = "Today";
		else if (monthDifference == 0) //If within the same month
			int_to_string(dateDifference, dueDate[i]);
		else if (monthDifference == 1 && dateDifference == 0)  //If an exact month apart e.g. 23/2 -> 23/3
			int_to_string(get_days_in_month(month), dueDate[i]);
		else if(monthDifference == 1 && ( dateDifference < 0 || dateDifference > 0)) //If it's in the next month, with a higher/lower date
			int_to_string(get_days_in_month(month) + dateDifference, dueDate[i]);
		else if(monthDifference > 1) { //Future month
			
			/* Get position of month in array */
			int pos = 0;
			for(int i = 0; i < 11; i++) {
				if(!strcmp(month, listOfMonths[i])) {
					pos = i;
					break;
				}
			}

			/* Add number of days in month for each month difference */
			int accumulatedDays = 0;
			for(int i = 0; i < monthDifference; i++)
				accumulatedDays += get_days_in_month(listOfMonths[i+pos]);
			
			if(dateDifference == 0) //If it's an exact x months ahead
				int_to_string(accumulatedDays, dueDate[i]);
			else
				int_to_string(accumulatedDays + dateDifference, dueDate[i]);

		} 

	}
}

void print_results(char *name[], char *assignment[], char *due[], char *time[], int noOfLines) {

	/* Printing Date Difference */
	for(int i = 0; i < noOfLines; i++) {
		
		if(!strcmp(name[i], " " ))
			break;

		printf("Coursework %d:\n", (i+1));
		printf("\tModule: %s \n\t%s\n", name[i], assignment[i]);
		if(!strcmp(due[i], "Passed") || !strcmp(due[i], "Today"))
			printf("\tDue: %s\n", due[i]);
		else 
			printf("\tDue: %s days @ %s\n\n", due[i], time[i]);

	}
}



int get_number_of_lines() {
	FILE *file = fopen("courseworklist.txt", "r"); //Need to hardlink
	int counter = 0;
	int line;

	while(!feof(file)) {
		line = fgetc(file);

		if(line == '\n')
			counter++;

	}


	fclose(file);
	return counter;
}

int get_month_number() {
	if(!strcmp(month, "Jan"))
		return 1;
	if(!strcmp(month, "Feb"))
		return 2;
	if(!strcmp(month, "Mar"))
		return 3;
	if(!strcmp(month, "Apr"))
		return 4;
	if(!strcmp(month, "May"))
		return 5;
	if(!strcmp(month, "Jun"))
		return 6;
	if(!strcmp(month, "Jul"))
		return 7;
	if(!strcmp(month, "Aug"))
		return 8;
	if(!strcmp(month, "Sep"))
		return 9;
	if(!strcmp(month, "Oct"))
		return 10;
	if(!strcmp(month, "Nov"))
		return 11;
	if(!strcmp(month, "Dec"))
		return 12;

	return 9000;
}

int get_days_in_month(char *param){
	if(!strcmp(param, "Jan"))
		return 31;
	if(!strcmp(param, "Feb"))
		return 28;
	if(!strcmp(param, "Mar"))
		return 31;
	if(!strcmp(param, "Apr"))
		return 30;
	if(!strcmp(param, "May"))
		return 31;
	if(!strcmp(param, "Jun"))
		return 30;
	if(!strcmp(param, "Jul"))
		return 31;
	if(!strcmp(param, "Aug"))
		return 31;
	if(!strcmp(param, "Sep"))
		return 30;
	if(!strcmp(param, "Oct"))
		return 31;
	if(!strcmp(param, "Nov"))
		return 30;
	if(!strcmp(param, "Dec"))
		return 31;

	return 9999;
}



//Possible re-alloc after all lines are read with >= 1 bad lines
void parse_file(char *name[], char *assignment[], char *due[], char *time[]) {

	FILE *file = fopen("courseworklist.txt", "r");
	if(errno) {
		perror("There was an error with opening courseworklist.txt");
		exit(1);
	}


	/* Reading the file 'til the end */
	int pos = 0, goodLine = 1;
	char *temp[PARAMETERS];
	while(!feof(file)) {

		char buff[BUFFER_SIZE];
		char character[2];
		character[1] = '\0';

		/* Building the line */
		for(int i = 0; i < 50; i++) {

			character[1] = fgetc(file);

			/* If the line is incomplete */
			if(feof(file)) 
				return;

			/* If the end of the line is reached */
			if(character[1] == '\n') {
				buff[i] = '\0';
				break;
			}

			buff[i] = character[1];	
		}

		/* Breaking the line into segments */
		temp[0] = strtok(buff, "|");
		if(temp[0] == NULL)
			return;
		
		for(int i = 1; i < PARAMETERS; i++) 
			temp[i] = strtok(NULL, "|");

		for(int i = 0; i < PARAMETERS; i++)
			if(temp[i] == NULL)
				goodLine = 0;

	    printf("Elements: %s %s %s %s\n", temp[0], temp[1], temp[2], temp[3]);
		
		if(goodLine) {

			memcpy(name[pos],temp[0], strlen(temp[0]));

			memcpy(assignment[pos],temp[1], strlen(temp[1]));

			memcpy(due[pos],temp[2], strlen(temp[2]));

			memcpy(time[pos], temp[3], strlen(temp[3]));

			pos++;
		}

		goodLine = 1;
	}
	

	fclose(file);
}

void int_to_string(int number, char dueDate[]) {
	char invertedBuf[11],realBuf[11];
	char *returnBuf;

	//printf("Orig: %d\n", number);
	
	for(int i = 0; i < 10; i++) {
		invertedBuf[i] = id_digit(number % 10); //Number is backwards
		number /= 10;

		//printf("Num after div: %d\n", number);

		if(number == 0) {
			invertedBuf[i+1] = '\0';
			realBuf[i+1] = '\0';
			break;
		}
	}

	
	int len = strlen(invertedBuf); //In the case the number was not 10 digits long
	
	for(int i = len-1; i >= 0; i--) {
	    realBuf[len - (i + 1)] = invertedBuf[i];
	}
	
	//printf("Inverted: %s\n", invertedBuf);
	//printf("Real: %s\n", realBuf);

	strcpy(dueDate, realBuf);	
}

void parse_date() {
	
	FILE *file;
	file = popen("date", "r");
	
	fscanf(file, "%s %s %s %s %s %s", day, month, date, currTime, timeZone, year);
	
	fclose(file);
}



char id_digit(int digit) {
	
	if(digit == 0)
		return '0';
	if(digit == 1)
		return '1';
	if(digit == 2)
		return '2';
	if(digit == 3)
		return '3';
	if(digit == 4)
		return '4';
	if(digit == 5)
		return '5';
	if(digit == 6)
		return '6';
	if(digit == 7)
		return '7';
	if(digit == 8)
		return '8';
	else
		return '9';
}
