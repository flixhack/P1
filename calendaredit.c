#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"
#define MAX_LINE_LENGTH 100


int main() {

    FILE *readFile = fopen("calendar.txt", "r");
    FILE *writeTemp = fopen("replace.tmp", "w");
    char buffer[MAX_LINE_LENGTH];
    char newLine[MAX_LINE_LENGTH];
    int line, count = 0, i;  
    char editDate[MAX_LINE_LENGTH];
    char editMonth[2];
    char editYear[4];
    char mode;

    //Give warning if unable to read calendar.txt
    if (readFile == NULL) {
        printf("Unable to open database.");
        exit(EXIT_FAILURE);
    }

    //Defining date1 and module1 for testing purposes
    date date1;

    date1.day = 3;
    date1.month = 2;
    date1.year = 2012;

    element module1;
    module1.time = 1130;
    module1.duration = 60;

    strcpy(module1.subject, "chemistry");

    printf("Month = %i\n", date1.month);

    //This is all for testing purposes. Final version would be done with input variables
    int modeLoop = 1;
    while(modeLoop == 1) {

        printf("What mode do you want to use? A/D/R: ");
        scanf(" %c", &mode);

        if (mode == 'D') {
            printf("Enter the line you want to delete: ");
            scanf("%i", &line);
            modeLoop = 0;
        }
        else if (mode == 'A' || mode == 'R') {
            printf("Enter the line you want to add by, or replace: ");
            scanf("%i", &line);

            printf("Enter the new line: ");
            scanf("%s", &newLine);

            strcat(newLine, "\n");
            modeLoop = 0;
        }
        else{
            printf("You entered an invalid character. Please try again.\n");
        }
    }

    //Reads through each line of the db, copies content to the temp file, and makes the requested change once it's location is found
    while ((fgets(buffer, MAX_LINE_LENGTH, readFile)) != NULL) {
        count++;

        if (count == line) {
            if (mode == 'D') {
                fputs("", writeTemp);
            }
            else if (mode == 'A') {
                strcat(buffer, newLine);
                fputs(buffer, writeTemp);
            }
            else if (mode == 'R') {
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

    return 0;
}
