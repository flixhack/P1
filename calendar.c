#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#define MAX_LINE_LENGTH 100

int countChars(char [], int);
int stringToInt(char []);
int main(int argc, char const *argv[]){

    char string[MAX_LINE_LENGTH];
    char calendar[MAX_LINE_LENGTH] = {0};
    int readSwitch = 0;
    int bytes = 0;
    int locOne, locTwo;
    int lineCount = 1;
    char longBoi[100][100];
    char timeRead[5];

    //Opens the text file, and returns an error if it cannot be found
    FILE *readFile = fopen("calendar.txt", "r");
    if (readFile == NULL){
        printf("Error: file missing\n");
        exit(EXIT_FAILURE);
    }

    printf("please enter the date you wish to search for: ");
    scanf("%s", calendar);
    //Terrible variable naming ahead. "calendar" is the string entered by the user to be searched for, "string" is the string from the text file
    while ( fscanf(readFile,"%s", string) == 1){
        ++bytes;
     
        //Checks if the current string is the string you are looking for. Assigns readSwitch, and the variables that indicate where the section you are looking for begins and ends
        if(strstr(calendar, string) != 0) {
            if (readSwitch == 0) {
                readSwitch = 1;
                locOne = bytes;
            }
            else if (readSwitch == 1) {
                locTwo = bytes;
            }
        }
    }

    //If statement uses the location variables assigned earlier (locOne and locTwo) to only print the necesarry text
    if (readSwitch == 1) {
        rewind(readFile);
        bytes = locOne;
        int j = 0;
        while (fscanf(readFile, "%s", string) == 1) {
            if (lineCount > bytes && lineCount < locTwo) {
                printf("[%i] %s", lineCount, string);
                strcpy(longBoi[j], string);
                j++;
                bytes++;
                if (string[strlen(string) - 1] != '\n') {
                    printf("\n");
                }
            }
        lineCount++;
        }
    }

    int giveUp;
    char giveDown[20];
    bytes = 0;
    char testInput[MAX_LINE_LENGTH];
    readSwitch = 0;
    int lineLoc;

    printf("\nDo the thing: ");
    scanf("%s", testInput);

    rewind(readFile);
    while (fscanf(readFile, "%s", string) == 1) {
        ++bytes;
        if (strstr(testInput, string) != 0) {
            lineLoc = bytes;
        }
    }

   printf("\nlineLoc: %i\n", lineLoc);


    /*
    printf("Enter the line contents you wish to search for: ");
    scanf("%s", giveDown);

    for (giveUp = 0; giveUp < MAX_LINE_LENGTH; giveUp++) {
        printf("\nlongBoi: %s", longBoi[giveUp]);
        if (longBoi[giveUp] == giveDown) {
            printf("\nNeat: [%i]\n", giveUp);
        }
        else {
            printf("\n:(\n");
        }
    }
    */

    int k;
    int x = lineLoc - 2;
    int parseSwitch;
    char entryTime[5][MAX_LINE_LENGTH];
    char entryType[5][4];
    char entrySubject[5][MAX_LINE_LENGTH];
    char entryDuration[5][MAX_LINE_LENGTH];
    int elementsInDate;

    elementsInDate = locTwo - locOne - 1;

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

    printf("\nentryType: %s\n", entryType[1]);

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
