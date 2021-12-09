#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 100

void databaseEdit(char *, int *, char *, char *);
void findSection(char *, int *, int *, char *, char *);
void readSection(char *, int *, int *, char [][100], char *);
void findLine(char *, int *, char *, int *, char *);
void calendarSplit(char [][100], int *, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][4], char [][MAX_LINE_LENGTH]);

int locOne = 0, locTwo = 0;

/*This function edits a given database file. Made can be set to 'D' to delete a given line, 'C' to create a new line
and 'R' to replace the text written on a given line.
lineNum is which line in the file to edit, newLine is the new text for use in C and R mode
databaseSelect is which text file the function accesses*/
void databaseEdit(char *mode, int *lineNum, char newLine[], char databaseSelect[]) {

    char buffer[MAX_LINE_LENGTH];
    int count = 0;
    FILE *readFile = fopen(databaseSelect, "r");
    FILE *writeTemp = fopen("replace.tmp", "w");

    if (readFile == NULL) {
        printf("Database file not found. Contact an administrator.");
        exit(EXIT_FAILURE);
    }

    //Reads through each line of the db, copies content to the temp file, and makes the requested change once it's location is found
    while ((fgets(buffer, MAX_LINE_LENGTH, readFile)) != NULL) {
        count++;

        if (count == *lineNum) {
            if (*mode == 'D') {
                fputs("", writeTemp);
            }
            else if (*mode == 'C') {
                strcat(buffer, newLine);
                strcat(buffer, "\n");                
                fputs(buffer, writeTemp);
            }
            else if (*mode == 'R') {
                strcat(newLine, "\n");
                fputs(newLine, writeTemp);
            }
        }
        else {
            fputs(buffer, writeTemp);
        }
    }

    fclose(readFile);
    fclose(writeTemp);

    //Replaces the old db file with the one that now has the desired corrections
    remove("calendar.txt");
    rename("replace.tmp", "calendar.txt");    
}

/*this function finds a start and a stop point in a certain section of a database. locOne being start, locTwo being end
  The start and end is determined by a certain string in the db that indicates the start, and once repeated indicates the end
  searchTerm indicates the term the function looks for to find locOne and locTwo*/
void findSection(char string[], int *locOne, int *locTwo, char searchTerm[], char databaseSelect[]) { 
    int bytes = 0, readSwitch = 0;

    //Opens the text file, and returns an error if it cannot be found    
    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    //Terrible variable naming ahead. "calendar" is the string entered by the user to be searched for, "string" is the string from the text file
    while ( fscanf(readFile,"%s", string) == 1){
     
        //Checks if the current string is the string you are looking for. Assigns readSwitch, and the variables that indicate where the section you are looking for begins and ends
        if(strstr(searchTerm, string) != 0) {
            if (readSwitch == 0) {
                readSwitch = 1;
                *locOne = bytes;
            }
            else if (readSwitch == 1) {
                *locTwo = bytes;
            }
        }
        bytes++;
    }
    fclose(readFile);   
}

/*This function can read the lines between locOne and locTwo and store them to the tempDB array*/
void readSection(char string[], int *locOne, int *locTwo, char tempDB[][100], char databaseSelect[]) {
    //If statement uses the location variables assigned earlier (locOne and locTwo) to only store the necesarry text
    int lineCount = 0, bytes = 0;
    
    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }    
    
    bytes = *locOne;
    int i = 0;
    while (fscanf(readFile, "%s", string) == 1) {
        if (lineCount > bytes && lineCount < *locTwo) {
            strcpy(tempDB[i], string);
            printf("readSection, string: %s, bytes: %i", string, bytes);
            i++;
            bytes++;
            if (string[strlen(string) - 1] != '\n') {
                printf("\n");
            }
        }
        lineCount++;
    }
    fclose(readFile);
}

/*This function can find a certain line of text from a string given from testInput, and saves the location to lineLoc*/
void findLine (char string[], int *lineLoc, char testInput[], int *locOne, char databaseSelect[]) {
    int bytes = 0;

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(readFile, "%s", string) == 1) {
        if (strstr(testInput, string) != 0) {
            *lineLoc = bytes - *locOne;
        }
        bytes++;    
    }

    *lineLoc = *lineLoc - 1;

    fclose(readFile);
}

/*This function is specifically for use with the calendar database, and splits the output from its functions into time, duration, type and subject*/
void calendarSplit (char tempDB[][100], int *lineLoc, char entryTime[][MAX_LINE_LENGTH], char entryDuration[][MAX_LINE_LENGTH], char entryType[][4], char entrySubject[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;

    *lineLoc;

    for (k = 0; k < MAX_LINE_LENGTH; k++) {
        if (tempDB[*lineLoc][k] == '_') {
            parseSwitch++;
        }
        else if (tempDB[*lineLoc][k] != '_' && parseSwitch == 1) {
            entryTime[*lineLoc][k] = tempDB[*lineLoc][k];
        }        
        else if (tempDB[*lineLoc][k] != '_' && parseSwitch == 2) {
            entryDuration[*lineLoc][k - countChars(tempDB[*lineLoc], 1)] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != '_' && parseSwitch == 3) {
            entryType[*lineLoc][k - countChars(tempDB[*lineLoc], 2)] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != '_' && parseSwitch == 4) {
            entrySubject[*lineLoc][k - countChars(tempDB[*lineLoc], 3)] = tempDB[*lineLoc][k];
        }
    }    
}

int countChars(char string[], int underscores){
    int underscoreCount = 0;
    int chars = 0;
    int i = 0;
    for (i = 0; underscoreCount != underscores && i < MAX_LINE_LENGTH; i++){
        chars++;
        if (string[i] == '_'){
            underscoreCount++;
        }
    }
    return chars;
}

//Converts a string of numbers to an integer
int stringToInt(char string[]){
    int i = 0;
    int res = 0;
    for (i = 0; string[i]; i++){    //if the char on string[i] is NULL, it returns false, thus ending the loop
        res = res * 10;
        res = res + (string[i] - '0');
    }
    return res;
}
