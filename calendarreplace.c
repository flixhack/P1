#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 100

//Defining structures, since they aren't included in any header file yet.
typedef struct date {
    int week,
        day,
        month,
        year;
    double hoursFree;
} date;

typedef struct module {
    date date1;
    int startTime;
    int duration;
    char subject[100];
} module;

int main() {

    FILE *readFile = fopen("calendar.txt", "r");
    FILE *writeTemp = fopen("replace.tmp", "w");
    char buffer[MAX_LINE_LENGTH];
    char newLine[MAX_LINE_LENGTH];
    int line, count = 0, i;  
    char editDate[MAX_LINE_LENGTH];
    char editMonth[2];
    char editYear[4];

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

    module module1;
    module1.startTime = 1130;
    module1.duration = 60;

    strcpy(module1.subject, "chemistry");

    //For some reason editMonth isn't given a value. Investigate
    //Converting the int values from the struct to strings
    sprintf(editDate, "%i", date1.day);
    sprintf(editMonth, "%i", date1.month);
    sprintf(editYear, "%i", date1.year);

    //Assembling all the parts of the date to result in a dd/mm/yyyy format for use in search
    strcat(editDate, "/");
    strcat(editDate, editMonth);
    strcat(editDate, "/");
    strcat(editDate, editYear);

    //For testing purposes
    printf("Woo: %s\n", editDate);
    
    //Turning startTime from module struct into string. Assembling startTime and subject into "time_subject" format for use in db
    sprintf(newLine, "%i", module1.startTime);
    strcat(newLine, "_");
    strcat(newLine, module1.subject);

    //For testing purposes
    printf("blah: %s\n", newLine);

    //Reads through each line of the db, copies content to the temp file, and replaces the correct string once found
    while ((fgets(buffer, MAX_LINE_LENGTH, readFile)) != NULL) {
        count++;

        if (count == line)
            fputs(newLine, writeTemp);
        else
            fputs(buffer, writeTemp);
    }

    fclose(readFile);
    fclose(writeTemp);

    //Replaces the old db file with the one that now has the desired corrections
    remove("calendar.txt");
    rename("replace.tmp", "calendar.txt");

    return 0;
}