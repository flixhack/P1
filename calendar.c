#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_LENGTH 100


int main(int argc, char const *argv[]){

    char string[MAX_LINE_LENGTH];
    char calendar[MAX_LINE_LENGTH] = {0};
    int readSwitch = 0;
    int bytes = 0;
    int locOne, locTwo;
    int lineCount = 1;

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
    /*Rewind returns to the start of the file in order for it to be read again
      fscanf reads the file. Also used earlier.
      If statement uses the location variables assigned earlier (locOne and locTwo) to only print the necesarry text */
    if (readSwitch == 1) {
        rewind(readFile);
        bytes = locOne;
        while (fscanf(readFile, "%s", string) == 1) {
            if (lineCount > bytes && lineCount < locTwo) {
                printf("[%i] %s", lineCount, string);
                bytes++;
                if (string[strlen(string) - 1] != '\n') {
                    printf("\n");
                }
            }
        lineCount++;
        }
    }
    fclose(readFile);
}