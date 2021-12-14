#include <stdio.h>
#include <stdlib.h>
#include "dbManager.h"
#include "structs.h"

void findLatestDate(char *, char [][100]);

int main() {
    char databaseSelect[100] = "calendar.txt", tempDB[100][100];
    date output;

    findLatestDate(databaseSelect, tempDB);
    printf("");
}

void findLatestDate(char databaseSelect[], char tempDB[][100]) {

    date output;

    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }
    int i;
    char entryDay[100][100], entryMonth[100][100], entryYear[100][100];


    readSection(-1, 13, tempDB, "calendar.txt");

    for (i = 0; i < 13; i++) {
    calendarDateSplit(tempDB, i, entryDay, entryMonth, entryYear);
    }

    int latestDate = 0, j;
    for (j = 0; j < 13; j++) {
        if (stringToInt(entryYear[j]) * 10000 + stringToInt(entryMonth[j]) * 100 + stringToInt(entryDay[j]) > latestDate) {
            printf("latestDate: %i, entryDay: %s\n", latestDate, entryDay[j]);
            latestDate = (stringToInt(entryYear[j]) * 10000) + (stringToInt(entryMonth[j]) * 100) + stringToInt(entryDay[j]);
            output.day = stringToInt(entryDay[j]);
            output.month = stringToInt(entryMonth[j]);
            output.year = stringToInt(entryYear[j]);
        }
    }

}