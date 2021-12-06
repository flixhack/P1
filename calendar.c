#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#define MAX_LINE_LENGTH 100

void something(char *, int *, int *, char *);
void test(int *, int *);
void another(char *, int *, int *, char [][100]);
void theThing(char *, int *);

int countChars(char [], int);
int stringToInt(char []);
int main(int argc, char const *argv[]){

    char string[MAX_LINE_LENGTH];
    int readSwitch;
    int bytes = 0;
    int locOne, locTwo, lineLoc;
    int lineCount = 1;
    char longBoi[100][100];
    char timeRead[5];
    char searchTerm[MAX_LINE_LENGTH];

    printf("Enter the search term: ");
    scanf("%s", searchTerm);

    something(string, &locOne, &locTwo, searchTerm);

    test(&locOne, &locTwo);

    another(string, &locOne, &locTwo, longBoi);

    theThing(string, &lineLoc);

    //Opens the text file, and returns an error if it cannot be found
    FILE *readFile = fopen("calendar.txt", "r");
    if (readFile == NULL){
        printf("Error: file missing\n");
        exit(EXIT_FAILURE);
    }

   printf("\nlineLoc: %i\n", lineLoc);

    int k;
    int x = lineLoc - 2;
    int parseSwitch;
    char entryTime[5][MAX_LINE_LENGTH];
    char entryType[5][4];
    char entrySubject[5][MAX_LINE_LENGTH];
    char entryDuration[5][MAX_LINE_LENGTH];

    parseSwitch = 1;
        for (k = 0; k < MAX_LINE_LENGTH; k++) {

            if (longBoi[x][k] == '_') {
                parseSwitch++;
            }
            else if (longBoi[x][k] != '_' && parseSwitch == 1) {
                entryTime[x][k] = longBoi[x][k];
            }        
            else if (longBoi[x][k] != '_' && parseSwitch == 2) {
                entryDuration[x][k - countChars(longBoi[x], 1)] = longBoi[x][k];
            }
            else if (longBoi[x][k] != '_' && parseSwitch == 3) {
                entryType[x][k - countChars(longBoi[x], 2)] = longBoi[x][k];
            }
            else if (longBoi[x][k] != '_' && parseSwitch == 4) {
                entrySubject[x][k - countChars(longBoi[x], 3)] = longBoi[x][k];
            }
        }

    fclose(readFile);

    int outputType = 0;

    if (entryType[x][0] == 'm') {
            outputType = 1;
    }
    else if (entryType[x][0] == 'a') {
            outputType = 2;
    }
    else if (entryType[x][0] == 'h') {
            outputType = 3;
    }
    else if (entryType[x][0] == 't') {
            outputType = 4;
    }

    element peepee;

    peepee.time = readTime(entryTime[x]);
    peepee.duration = stringToInt(entryDuration[x]);
    peepee.subject = entrySubject[x];
    peepee.type = outputType;

    printf("Time: %i, Duration: %i, Subject: %s, Type: %i\n", peepee.time, peepee.duration, peepee.subject, peepee.type);

}

/*this function finds a start and a stop point in a certain section of a database. locOne being start, locTwo being end
  The start and end is determined by a certain string in the db that indicates the start, and once repeated indicates the end*/
void something(char string[], int *locOne, int *locTwo, char searchTerm[]) { 
    int bytes = 0, readSwitch = 0;

    //Opens the text file, and returns an error if it cannot be found    
    FILE *readFile = fopen("calendar.txt", "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }

    //Terrible variable naming ahead. "calendar" is the string entered by the user to be searched for, "string" is the string from the text file
    while ( fscanf(readFile,"%s", string) == 1){
        ++bytes;
     
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
    }
    fclose(readFile);   
}

void test(int *locOne, int *locTwo) {
    printf("test locOne: %i, locTwo: %i\n", *locOne, *locTwo);
}

void another(char string[], int *locOne, int *locTwo, char longBoi[][100]) {
    //If statement uses the location variables assigned earlier (locOne and locTwo) to only print the necesarry text
    int lineCount = 1, bytes;
    
    FILE *readFile = fopen("calendar.txt", "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }    
    
    bytes = *locOne;
    int i = 0;
    while (fscanf(readFile, "%s", string) == 1) {
        if (lineCount > bytes && lineCount < *locTwo) {
            printf("[%i] %s", lineCount, string);
            strcpy(longBoi[i], string);
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

void theThing (char string[], int *lineLoc) {
    
    FILE *readFile = fopen("calendar.txt", "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }    
    
    int bytes = 0, readSwitch = 0;
    char testInput[MAX_LINE_LENGTH];

    printf("\nDo the thing: ");
    scanf("%s", testInput);

    rewind(readFile);
    while (fscanf(readFile, "%s", string) == 1) {
        ++bytes;
        if (strstr(testInput, string) != 0) {
            *lineLoc = bytes;
        }
    }
    fclose(readFile);
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
int stringToInt(char string[]){
    int i = 0;
    int res = 0;
    for (i = 0; string[i]; i++){    //if the char on string[i] is NULL, it returns false, thus ending the loop
        res = res * 10;
        res = res + (string[i] - '0');
    }
    return res;
}
