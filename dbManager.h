#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 100

void databaseEdit(char *, int *, char *, char *);
void findSection(char *, char *, int *, int *);
void readSection(int, int, char [][100], char *);
int findLineLoc(char *, int, char *);
void calendarSplit(char [][100], int, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][4], char [][MAX_LINE_LENGTH]);
int countChars(char *, int, char);
void lineSplit(char [][100], int *, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH]);

int locOne = 0, locTwo = 0;

/*This function edits a given database file. Made can be set to 'D' to delete a given line, 'C' to create a new line
and 'E' to replace the text written on a given line.
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
            if (*mode == 'D' || *mode == 'd') {
                fputs("", writeTemp);
            }
            else if (*mode == 'C' || *mode == 'c') {
                strcat(buffer, newLine);
                strcat(buffer, "\n");
                fputs(buffer, writeTemp);
            }
            else if (*mode == 'E' || *mode == 'e') {
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

/*This function can find a certain line of text from a string given from testInput, and saves the location to lineLoc
  locOne is set to 0, it will simply find the line that a certain string is on.
  Otherwise you can use locOne as an offset, in you maybe want to only search for the string in a given section. Remember this requires you to use locOne - 1*/
int findLineLoc (char testInput[], int locOne, char databaseSelect[]) {
    int bytes = 0, lineLoc = 0;
    char string[MAX_LINE_LENGTH];

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(readFile, "%s", string) == 1) {
        if (strstr(testInput, string) != 0) {
            lineLoc = bytes - locOne;
        }
        bytes++;
    }

    fclose(readFile);
    return lineLoc;
}

/*This function will find the start and stop points of a given section. It looks for "testInput" for locOne,
  and then looks for "testInpuT_END" for locTwo*/
void findSection (char testInput[], char databaseSelect[], int *locOne, int *locTwo) {
    char inputTwo[MAX_LINE_LENGTH];
    int i;
    for (i = 0; i < MAX_LINE_LENGTH; i++) {
        inputTwo[i] = testInput[i];
    }
    strcat(inputTwo, "_END");
    *locOne = findLineLoc(testInput, 0, databaseSelect);
    *locTwo = findLineLoc(inputTwo, 0, databaseSelect);
}

/*This function can read the lines between locOne and locTwo and store them to the tempDB array.
  In the tempDB */
void readSection(int locOne, int locTwo, char tempDB[][100], char databaseSelect[]) {
    //If statement uses the location variables assigned earlier (locOne and locTwo) to only store the necesarry text
    int lineCount = 0, bytes = 0;
    char string[MAX_LINE_LENGTH];

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    bytes = locOne;
    int i = 0;
    while (fscanf(readFile, "%s", string) == 1) {
        if (lineCount > bytes && lineCount < locTwo) {
            strcpy(tempDB[i], string);
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

/*This function is specifically for use with the calendar database, and splits the output from its functions into time, duration, type and subject*/
void calendarSplit (char tempDB[][100], int lineLoc, char entryTime[][MAX_LINE_LENGTH], char entryDuration[][MAX_LINE_LENGTH], char entryType[][4], char entrySubject[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;

    for (k = 0; k < MAX_LINE_LENGTH; k++) {
        if (tempDB[lineLoc][k] == '_') {
            parseSwitch++;
        }
        else if (tempDB[lineLoc][k] != '_' && parseSwitch == 1) {
            entryTime[lineLoc][k] = tempDB[lineLoc][k];
        }
        else if (tempDB[lineLoc][k] != '_' && parseSwitch == 2) {
            entryDuration[lineLoc][k - countChars(tempDB[lineLoc], 1, '_')] = tempDB[lineLoc][k];
        }
        else if (tempDB[lineLoc][k] != '_' && parseSwitch == 3) {
            entryType[lineLoc][k - countChars(tempDB[lineLoc], 2, '_')] = tempDB[lineLoc][k];
        }
        else if (tempDB[lineLoc][k] != '_' && parseSwitch == 4) {
            entrySubject[lineLoc][k - countChars(tempDB[lineLoc], 3, '_')] = tempDB[lineLoc][k];
        }
    }
}

int countChars(char string[], int underscores, char charToCount){
    int charCount = 0;
    int chars = 0;
    int i = 0;
    for (i = 0; charCount != underscores && i < MAX_LINE_LENGTH; i++){
        chars++;
        if (string[i] == charToCount){
            charCount++;
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

void lineSplit (char tempDB[][100], int *lineLoc, char userID[][MAX_LINE_LENGTH], char usernameAndPassword[][MAX_LINE_LENGTH], char loginID[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;
    //printf("\nlineSplit: [%i] %s", *lineLoc, tempDB[*lineLoc]);

    for (k = 0; k < MAX_LINE_LENGTH; k++) {
        if (tempDB[*lineLoc][k] == ';') {
            parseSwitch++;
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 1) {
            userID[*lineLoc][k] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 2) {
            usernameAndPassword[*lineLoc][k - countChars(tempDB[*lineLoc], 1, ';')] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 3) {
            loginID[*lineLoc][k - countChars(tempDB[*lineLoc], 2, ';')] = tempDB[*lineLoc][k];
        }
    }
}
