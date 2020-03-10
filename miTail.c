/* @author Near

Linux Tail program implementation.

Reading lines from the stdin, Tail prints the last 10 lines by default to the stdout.
Use -n switch to change this default value.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 5     //Maximum lines that the program can read
#define MAXLENGTH 255 //Maximum length of a line
#define MAXLENGTH 255 //Maximum length of a line
#define NLINES 10     //Default number of lines to print

char* lines[MAXSIZE]; //Array that holds the pointers to the strings

void tail(int,int); //This will do the printing logic, parameters: from array element index, to array element index.
void end(int);		//Free up resources, parameter: number of lines that had been read.
int migetline(char*, int); //My getline implementation, it needs the string and the maximum length, returns the length of the line, -1 if empty row is entered.
int miAtoi(char* p); //My atoi implementation, it needs the string, returns the integer.

int main(int argc, char* argv[]) {

	int linesRead = 0; //Number of lines read.
	int linesToPrint = NLINES; //Number of lines to print
	char* line = NULL; //Temporary pointer to a single line.

	/* Check if there is -n switch. If so set the new value to linesToPrint*/
	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		linesToPrint = miAtoi(argv[2]);
	}

	/* Allocate memory for the first line */
	line = (char*)malloc(MAXLENGTH * sizeof(char));

	/* Read lines until maximum number of lines reached, out of memory or empty line is entered. */
	while (linesRead < MAXSIZE && line && migetline(line, MAXLENGTH) > -1) {

		lines[linesRead] = line;
		++linesRead;
		line = (char*)malloc(MAXLENGTH * sizeof(char));
	}
	
	tail(linesRead - linesToPrint,linesRead);
	free(line); //The last "line" is not added into lines[]. Free up here.
	end(linesRead); //Free resources held by lines.
	
	return 0;
}

void tail(int from,int to) {
	puts("Tail: ");
	for (int i = from; i < to; ++i) {
		if (lines[i] != NULL)
			printf("%s",lines[i]);
	}

}

//free up resources
void end(int linesRead) {
	for (int i = 0; i < linesRead;++i) {
		if (lines[i] != NULL)
			free(lines[i]);
	}

}

int miAtoi(char* p) {

	int number = 0;

	while (*p != '\0') {
		if (isdigit(*p)) {
			number *= 10;
			number += (*p - '0');
		}
	++p;
	}
	return number;
}

int migetline(char* s, int lim) {

	char c;
	int i;
	for (i = 0; i < lim && ((c = getchar()) != '\n'); ++i) {
		*(s + i) = c;
	}
	if (c == '\n') {
		if (i == 0) {
		//The user entered an empty row.
			*(s) = '\0';
			return -1;
		}
		*(s + i) = '\n';
		++i;
	}
	*(s + i) = '\0';

	return i;
}
