#include <stdio.h>
#include <stdlib.h>
#include "dbManager.h"

char searchTerm[100], blah[100], database[100] = "calendar.txt", tempDB[100][100];
int lineLoc;
char entryTime[100][100], entryDuration[100][100], entryType[100][4], entrySubject[100][100], endDate[100][10];

int main() {
    printf("Enter the searchterm: ");
    scanf(" %s", searchTerm);

    findSection(searchTerm, database, &locOne, &locTwo);
    readSection(-1, 15, tempDB, database);
    
    int i;
    for (i = 0; i < 10; i++) {
        printf("[%i] %s\n", i, tempDB[i]);
    }

    // printf("Enter the line to split: ");
    // scanf(" %s", blah);

    findLineLoc (blah, locOne, database);

    int k;
    for (k = 0; k < 10; k++) {
    calendarSplit(tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
    }

    int j;
    for (j = 0; j < 10; j++) {
    printf("[%i] entryTime: %s, entryDuration: %s, entryType: %s, entrySubject: %s, endDate: %s\n", j, entryTime[j], entryDuration[j], entryType[j], entrySubject[j], endDate[j]);
    }
}