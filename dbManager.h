#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void databaseEdit(char *, int *, char *, char *);
void findSection(char *, char *, int *, int *);
void readSection(int, int, char [][100], char *);
int findLineLoc(char *, int, char *);
void calendarSplit(char [][100], int, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][4], char [][MAX_LINE_LENGTH], char[][10]);
int countChars(char *, int, char), countLines(char *);
void lineSplit(char [][100], int *, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH]);
int countCharNum(char[], char, int);

int locOne = 0, locTwo = -1;

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
        if (strcmp(testInput, string) == 0) {
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
void readSection(int locOne, int locTwo, char tempDB[][MAX_LINE_LENGTH], char databaseSelect[]) {
    //If statement uses the location variables assigned earlier (locOne and locTwo) to only store the necesarry text
    int lineCount = 0, bytes = 0;
    char string[MAX_LINE_LENGTH];

    memset(tempDB, '\0', MAX_LINE_LENGTH);

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    bytes = locOne;
    int i = 0;
    //If statement uses the location variables assigned earlier (locOne and locTwo) to only store the necesarry text
    while (fscanf(readFile, "%s", string) == 1) {
        if (lineCount > bytes && lineCount < locTwo) {
            strcpy(tempDB[i], string);
            i++;
            bytes++;

        }
        lineCount++;
    }
    fclose(readFile);
}

int countCharNum(char string[], char searchTerm, int lengthOfString){
  int numOfChar = 0;
  for (int i = 0; i < lengthOfString; i++) {
    if (string[i] == searchTerm) {
      numOfChar++;

    }
  }
  return numOfChar;
}

/*This function is specifically for use with the calendar database, and splits the output from its functions into time, duration, type and subject*/
void calendarSplit (char tempDB[][MAX_LINE_LENGTH], int lineLoc, char entryTime[][MAX_LINE_LENGTH], char entryDuration[][MAX_LINE_LENGTH], char entryType[][4], char entrySubject[][MAX_LINE_LENGTH], char endDate[][10]) {
    int endCheck;
    char *endend;

    char tempEntryTime[100], tempEntryDuration[100], tempEntrySubject[100], tempEntryType[100], tempEndDate[100];

    for (int j = 0; j < 100; j++) {
      tempEntryTime[j] = '\0';
      tempEntryDuration[j] = '\0';
      tempEntrySubject[j] = '\0';
      tempEntryType[j] = '\0';
      tempEndDate[j] = '\0';
    }




    for (int i = 0; i < MAX_LINE_LENGTH; i++) {
        entryDuration[lineLoc][i] = '\0';
        entryTime[lineLoc][i] = '\0';
        entrySubject[lineLoc][i] = '\0';
        if (i <= 3) {
            entryType[lineLoc][i] = '\0';
        }
        if (i <= 9) {
            endDate[lineLoc][i] = '\0';
        }
    }



    char *token;
    const char s[2] = "_";

    token = strtok(tempDB[lineLoc], s);





    for (int j = 0; j < 5 && token != NULL; j++) {
        if (j == 0 && token != NULL) {
        strcpy(tempEntryTime, token);
        strcpy(entryTime[lineLoc], tempEntryTime);
        }
        else if (j == 1 && token != NULL) {
          endend = token;
          endCheck = strcmp("END", endend);
          if (endCheck != 0) {
            strcpy(tempEntryDuration, token);
            strcpy(entryDuration[lineLoc], tempEntryDuration);
          }
          else {
            strcpy(tempEntryDuration, token);
          }
        }
        else if (j == 2 && token != NULL) {
        strcpy(tempEntryTime, token);
        strcpy(entryTime[lineLoc], tempEntryTime);
        }
        else if (j == 3 && token != NULL) {
        strcpy(tempEntrySubject, token);
        strcpy(entrySubject[lineLoc], tempEntrySubject);
        }
        else if (j == 4 && token != NULL) {
        strcpy(tempEndDate, token);
        strcpy(endDate[lineLoc], tempEndDate);
        }
        else if (j == 0 && token == NULL) {
        strcpy(tempEntryTime, "1111");
        }
        else if (j == 1 && token == NULL) {
        strcpy(tempEntryDuration, "1111");
        }
        else if (j == 2 && token == NULL) {
        strcpy(tempEntryType, "1111");
        }
        else if (j == 3 && token == NULL) {
        strcpy(tempEntrySubject, "1111");
        }
        else if (j == 4 && token == NULL) {
        strcpy(tempEndDate, "1111");
        }
        token = strtok(NULL, s);
    }


}

void calendarDateSplit (char tempDB[][100], int lineLoc, char entryDay[][MAX_LINE_LENGTH], char entryMonth[][MAX_LINE_LENGTH], char entryYear[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;

    for (k = 0; k < MAX_LINE_LENGTH; k++) {
        if (tempDB[lineLoc][k] == '/') {
            parseSwitch++;
        }
        else if (tempDB[lineLoc][k] != '/' && parseSwitch == 1) {
            entryDay[lineLoc][k] = tempDB[lineLoc][k];
        }
        else if (tempDB[lineLoc][k] != '/' && parseSwitch == 2) {
            entryMonth[lineLoc][k - countChars(tempDB[lineLoc], 1, '/')] = tempDB[lineLoc][k];
        }
        else if (tempDB[lineLoc][k] != '/' && parseSwitch == 3) {
            entryYear[lineLoc][k - countChars(tempDB[lineLoc], 2, '/')] = tempDB[lineLoc][k];
        }
    }
}

int countChars(char string[], int underscores, char charToCount) {
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

int countLines(char *filename){
    FILE *readFile = fopen(filename,"r");
    int lines = 0;
    int chars = 0;

    if (readFile == NULL){
        return 0;
    }
    lines++;
    while ((chars = fgetc(readFile)) != EOF){
        if (chars == '\n'){
            lines++;
        }
    }
    fclose(readFile);
    return lines;
}

//returns 1 if the char "searchTerm" is present in the given string. Otherwise returns 0.
int containsChar(char string[], char searchTerm) {
    int isPresent = 0, i, run = 1;
    int stringLength;
    stringLength = strlen(string);

    for(i = 0; i < stringLength && run == 1; i++) {
        if (string[i] == searchTerm) {
            isPresent = 1;
        }
        else if (string[i] == '\n' || string[i] == ' ') {
            run = 0;
        }
    }
    return isPresent;
}

date findLatestDate(char databaseSelect[]) {
    int totalLines;
    totalLines = countLines(databaseSelect);
    char tempDB[totalLines][100];
    date output;

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }
    int i;
    char entryDay[100][100], entryMonth[100][100], entryYear[100][100];
    int lineCount = countLines(databaseSelect);

    readSection(-1, lineCount, tempDB, "calendar.txt");

    for (i = 0; i < lineCount; i++) {
    calendarDateSplit(tempDB, i, entryDay, entryMonth, entryYear);
    }

    int latestDate = 0, j;
    for (j = 0; j < lineCount; j++) {
        if (containsChar(tempDB[j], '/') == 1 && containsChar(tempDB[j], '_') == 0) {
            if (atoi(entryYear[j]) * 10000 + atoi(entryMonth[j]) * 100 + atoi(entryDay[j]) > latestDate) {
                latestDate = (atoi(entryYear[j]) * 10000) + (atoi(entryMonth[j]) * 100) + atoi(entryDay[j]);
                output.day = atoi(entryDay[j]);
                output.month = atoi(entryMonth[j]);
                output.year = atoi(entryYear[j]);
            }
        }
    }
    return output;
}
void lineSplit (char tempDB[][100], int *lineLoc, char userID[][MAX_LINE_LENGTH], char usernameAndPassword[][MAX_LINE_LENGTH], char loginID[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;

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
