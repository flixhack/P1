#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#define MAX_LINE_LENGTH 100

void databaseEdit(char *, int *, char *);


int main() {
    char mode, newLine[MAX_LINE_LENGTH];
    int line;

    printf("Enter mode: ");
    scanf(" %c", &mode);

    printf("Enter line: ");
    scanf(" %i", &line);

    printf("Enter newLine: ");
    scanf(" %s", newLine);

    databaseEdit(&mode, &line, newLine);

    return 0;
}

void databaseEdit(char *mode, int *line, char newLine[]) {

    char buffer[MAX_LINE_LENGTH];
    int count = 0, i;  
    FILE *readFile = fopen("calendar.txt", "r");
    FILE *writeTemp = fopen("replace.tmp", "w");

    if (readFile == NULL) {
        printf("Database file not found. Contact an administrator.");
        exit(EXIT_FAILURE);
    }

    //Reads through each line of the db, copies content to the temp file, and makes the requested change once it's location is found
    while ((fgets(buffer, MAX_LINE_LENGTH, readFile)) != NULL) {
        count++;

        if (count == *line) {
            if (*mode == 'D') {
                fputs("", writeTemp);
            }
            else if (*mode == 'A') {
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