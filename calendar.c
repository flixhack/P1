#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "functions.h"
#define MAX_LINE_LENGTH 100

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
        if(strstr(calendar, string)!=0) {
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
    int x;
    int parseSwitch;
    char entryTime[5][MAX_LINE_LENGTH];
    char entryType[5][MAX_LINE_LENGTH];
    char entrySubject[5][MAX_LINE_LENGTH];
    int elementsInDate;

    elementsInDate = locTwo - locOne - 1;

    for (x = 0; x < elementsInDate; x++) {
        parseSwitch = 1;
        for (k = 0; k < 20; k++) {

            if (longBoi[x][k] == '_') {
                parseSwitch++;
            }
            else if (longBoi[x][k] != '_' && parseSwitch == 1) {
                entryTime[x][k] = longBoi[x][k];
            }        
            else if (longBoi[x][k] != '_' && parseSwitch == 2) {
                entryType[x][k - 5] = longBoi[x][k];
            }
            else if (longBoi[x][k] != '_' && parseSwitch == 3) {
                entrySubject[x][k - 9] = longBoi[x][k];
            }
        }

    }

    fclose(readFile);
}
