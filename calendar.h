#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "dbManager.h"
#define DAILY_SCHOOL_HOURS 9


int determineLeapYear(int year){
    if ((year% 4 == 0 && year%100 != 0) || year%400 == 0){
        return 1;
    }
    else {
        return 0;
    }
}


int daysInMonth(int month, int year){
    int days = 0;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        days = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11){
       days = 30;
    }
    else if (month == 2){
        if (determineLeapYear(year) == 1){
            days = 29;
        }
        else {
           days = 28;
       }
    }
    return days;
}

int remainingDaysInYear(date givenDate){ // count remaining days in the current year
    int days = 0;
    date counter = givenDate;
    days += daysInMonth(counter.month, counter.year) - counter.day + 1; //counts remaining days in current month. +1 to account for current day
    counter.month++;
    while (counter.month <= 12){
        days += daysInMonth(counter.month, counter.year);
        counter.month++;
    }
    return days;
}
int daysBetweenDates(date startDate, date endDate){ //counts days between two dates, including the start and end date
    int days = 0;
    date counter = startDate;
    if (endDate.year - counter.year != 0){ 
        days += remainingDaysInYear(counter);
        counter.day = 1;
        counter.month = 1;
        counter.year += 1;
    }
    if (counter.year < endDate.year){ //if someone is crazy enough to set an element to more than a year in the future
        while (counter.year < endDate.year){
            if (determineLeapYear(counter.year) == 1){
                days += 366;
            }
            else {
                days += 365;
            }
            counter.year++;
        }
    }
    if (counter.month < endDate.month){
        days += daysInMonth(counter.month, counter.year) - counter.day + 1; //first we count the remaining days in the current month
        counter.day = 1;
        counter.month++;
        while (counter.month < endDate.month){ //counts the full months until we are at the endDate month
            days += daysInMonth(counter.month, counter.year);
            counter.month++;
        }
    }
    while (counter.day <= endDate.day){
        counter.day++;
        days++;
    }
    return days;
}

void populateCalendar(date calendar[], date startDate, int size){
    int i = 0;
    date counter = startDate;
    int run = 1;
    while (run == 1){
        // printf("Counter date: %i/%i/%i\n", counter.day, counter.month, counter.year);
        // printf("startdate: %i/%i/%i\n", startDate.day, startDate.month, startDate.year);
        int daysInCurrentMonth = daysInMonth(counter.month, counter.year);
        // printf("Days in current month: %i\n", daysInCurrentMonth);
        // printf("counter.day: %i\n", counter.day);
        // printf("i: %i\n", i);
        //printf("Size of calendar: %i\n", (size));
        while (counter.day <= daysInCurrentMonth && i != (size)){
            calendar[i].year = counter.year;
            calendar[i].month = counter.month;
            calendar[i].day = counter.day;
            calendar[i].hoursFree = DAILY_SCHOOL_HOURS + 0.0;
            i++;
            counter.day++;
            //printf("Populated one element with a date\n"); //TESTING
        }
        counter.month++;
        counter.day = 1;
        if (counter.month == 13){
            counter.month = 1;
            counter.year++;
        }
        if (i == size){
            run = 0;
        }
    }
}

void dateToString(date calendar[], int i, char string[]){
    sprintf(string, "%i/%i/%i", calendar[i].day, calendar[i].month, calendar[i].year);
    //printf("Day: %i\n", calendar[i].day); //TESTING
}

void deductModulesFromHoursFree(date calendar[], int size){
    int totalLines;
    totalLines = countLines("calendar.txt");
    char tempDB[totalLines][MAX_LINE_LENGTH];
    char entryTime[totalLines][MAX_LINE_LENGTH];
    char entryDuration[totalLines][MAX_LINE_LENGTH];
    char entryType[totalLines][4];
    char entrySubject[totalLines][MAX_LINE_LENGTH];
    char endDate[totalLines][10];
    char string[10];
    //int lineLoc;
    int i = 0;
    int k = 0;
    for (i = 0; i < size; i++){
        dateToString(calendar, i, string);
        printf("%s\n", string); //TESTING
        findSection(string, "calendar.txt", &locOne, &locTwo);
        printf("locOne: %i  locTwo: %i\n", locOne, locTwo);
        readSection(locOne, locTwo, tempDB, "calendar.txt");
        if (locTwo + locOne != 0){
            for (k = 0; k <= (locTwo - locOne); k++){
                calendarSplit (tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
            }
            for (k = 0; k <= (locTwo - locOne); k++){
                int test = strcmp(entryType[k], "mod");
                if (test == 0){
                    int duration;
                    duration = atoi(entryDuration[k]);
                    printf("entryDuration: %s\n", entryDuration[k]);
                    printf("Duration int: %i\n", duration);

                    calendar[i].hoursFree -= ((duration + 0.0) / 60.0);
                    printf("Hours: %lf\n", ((duration + 0.0) / 60.0));
                    printf("hoursFree efter deduktion af moduler: %lf\n", calendar[i].hoursFree);
                }
            }
        }
    }
}

date stringToDate(char string[], char separator){
    printf("String going into stringToDate: %s (using seperator %c)\n", string, separator);
    date date;
    int parseSwitch = 1, k;
    char day[3];
    char month[3];
    char year[5];
    int dayNumCount = 0;
    int monthNumCount = 0;
    int yearNumCount = 0;
    int lineLength;
    lineLength = strlen(string);
    for (k = 0; k < lineLength; k++) {
        if (string[k] == separator) {
            parseSwitch++;
        }
        else if (string[k] != separator && parseSwitch == 1) {
            day[dayNumCount] = string[k];
            //printf("%c", string[k]);
            dayNumCount++;
        }
        else if (string[k] != separator && parseSwitch == 2) {
            month[monthNumCount] = string[k];
            //printf("%c", string[k]);
            monthNumCount++;
        }
        else if (string[k] != separator && parseSwitch == 3) {
            year[yearNumCount] = string[k];
            //printf("%c", string[k]);
            yearNumCount++;
        }
    }
    day[dayNumCount] = '\0';
    month[monthNumCount] = '\0';
    year[yearNumCount] = '\0';
    printf("\n");
    printf("month: %s\n", month);
    date.day = stringToInt(day);
    date.month = stringToInt(month);
    date.year = stringToInt(year);
    //printf("%i/%i/%i\n",date.day, date.month, date.year);
    printf("month[]: %s\n", month);


    return date;
}

date scanForEarliestAssignmentDate(char databaseSelect[]){
    printf("Reading from %s\n", databaseSelect);
    date earliestAssDate;
    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }
    int lineCount = countLines(databaseSelect);
    int i;
    char tempDB[lineCount][MAX_LINE_LENGTH];
    char entryTime[lineCount][100], entryDuration[lineCount][100], entryType[lineCount][4], entrySubject[lineCount][100], endDate[lineCount][10];

    readSection(-1, lineCount, tempDB, databaseSelect);
    for (i = 0; i < lineCount; i++) {
        printf("[%i] %s\n", i, tempDB[i]);
    }
    int k;
    for (k = 0; k < lineCount + 1; k++) {
        calendarSplit(tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
    }
    int j;
    int earliestDate = 100000000;
    for (j = 0; j < lineCount; j++){
        if (containsChar(tempDB[j], '-') == 1) {
            printf("Copying date to tempDate using stringToDate...\n");
            date tempDate = stringToDate(endDate[j], '-');
            printf("tempDate: %i/%i/%i\n", tempDate.day, tempDate.month, tempDate.year);
            if (tempDate.year * 10000 + tempDate.month * 100 + tempDate.day < earliestDate) {
                earliestDate = tempDate.year * 10000 + tempDate.month * 100 + tempDate.day;
                earliestAssDate.day = tempDate.day;
                earliestAssDate.month = tempDate.month;
                earliestAssDate.year = tempDate.year;
                printf("earliestDate: %i, entryDay: %i, entryMonth: %i, entryYear: %i\n", earliestDate, tempDate.day, tempDate.month, tempDate.year);
            }
        }
    }
    return earliestAssDate;
}

int calcAssignmentWorkLoad(const int i, date calendar[], int size, char entryType[][4], char entryDuration[][MAX_LINE_LENGTH], char endDate[][10]){
    int k;
    int j;
    int daysBetween;
    int fitsEasy = 0;
    date compareDateStart;
    double averageTime;
    double durationDouble;
    for (k = 0; k < (locTwo - locOne + 1); k++){
        printf("locOne: %i. locTwo: %i\n", locOne, locTwo);
        int test = strcmp(entryType[k], "ass");
        if (test == 0){
            compareDateStart = stringToDate(endDate[k], '-');
            //calendar[i] er vores compareDateEnd
            durationDouble = (atoi(entryDuration[k])) / 60.0;
            daysBetween = daysBetweenDates(compareDateStart, calendar[i]) - 2;
            averageTime = (durationDouble / daysBetween);
            printf("Average time: %lf\n", averageTime); //TESTING ONLY
            printf("Total time: %lf\n", durationDouble);
            fitsEasy = 1;
            for (j = (i - daysBetween); j < i && fitsEasy != 0; j++){
                printf("Day is %i/%i/%i. hoursFree: %lf\n", calendar[j].day, calendar[j].month, calendar[j].year, calendar[j].hoursFree);
                if (calendar[j].hoursFree < averageTime){
                    fitsEasy = 0;
                    printf("Doesn't fit easy\n");
                }
            }
            if (fitsEasy == 1){
                printf("Fits easy\n");
                for (j = (i - daysBetween); j < i; j++){
                    printf("hoursFree before deducting in date %i/%i/%i: %lf\n",calendar[j].day, calendar[j].month, calendar[j].year, calendar[j].hoursFree);
                    calendar[j].hoursFree -= averageTime;
                    printf("hoursFree after deducting in date %i/%i/%i: %lf\n",calendar[j].day, calendar[j].month, calendar[j].year, calendar[j].hoursFree);
                }
            }
            else {
                double accumulator = 0.0;
                for (j = (i - daysBetween); j < i; j++){
                    accumulator += calendar[j].hoursFree;
                }
                durationDouble = (stringToInt(entryDuration[k]) / 60.0);
                if (accumulator >= durationDouble){
                    printf("Fits\n");
                    for (j = (i - daysBetween); j < i; j++){
                        printf("hoursFree before: %lf\n", calendar[j].hoursFree);
                        durationDouble -= calendar[j].hoursFree;
                        if (durationDouble < 0){
                            calendar[j].hoursFree = (durationDouble * -1);
                        }
                        else {
                            calendar[j].hoursFree = 0;
                        }
                        printf("hoursFree after: %lf\n", calendar[j].hoursFree);
                    }
                }
                else {
                    printf("Doesn't fit\n");
                    return 0;
                }
            }
        }
    }
    return 1;
}

int deductAssignmentsFromHoursFree(date calendar[], int size){
    int totalLines = 0;
    totalLines = countLines("calendar.txt");
    char entryTime[totalLines][MAX_LINE_LENGTH];
    char entryDuration[totalLines][MAX_LINE_LENGTH];
    char entryType[totalLines][4];
    char entrySubject[totalLines][MAX_LINE_LENGTH];
    char tempDB[totalLines][MAX_LINE_LENGTH];
    char endDate[totalLines][10];
    char string[10];
    int i = 0;
    int k = 0;
    int returnValue;
    for (i = 0; i < size; i++){
        dateToString(calendar, i, string);
        //printf("%s", string); //TESTING
        findSection(string, "calendar.txt", &locOne, &locTwo);
        readSection(locOne, locTwo, tempDB, "calendar.txt");
        for (k = 0; k <= (locTwo - locOne); k++){
            calendarSplit (tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
        }
        printf("entering calcAssignmentWorkLoad on %i/%i/%i\n",calendar[i].day, calendar[i].month, calendar[i].year);
        returnValue = calcAssignmentWorkLoad(i, calendar, size, entryType, entryDuration, endDate);
    }
    return returnValue;
}

int calcWorkLoad(element newElement){
    int result = 0;
    int daysBetween = 0,
        size = 0;
    date earliestDate;
    printf("\nScanning for earliest assignment...\n");
    earliestDate = scanForEarliestAssignmentDate("calendar.txt");
    date latestDate;
    printf("\nScanning for latest date...\n");
    latestDate = findLatestDate("calendar.txt");
    printf("Latest date: %i/%i/%i\n", latestDate.day, latestDate.month, latestDate.year);
    date counter = earliestDate;
    printf("Earliest date: %i/%i/%i\n", earliestDate.day, earliestDate.month, earliestDate.year);
    //printf("newElement.startDate: %i/%i/%i\n", newElement.startDate.day, newElement.startDate.month, newElement.startDate.year);
    printf("\nCalculating days between dates...\n");
    daysBetween = daysBetweenDates(earliestDate, latestDate);
    printf("\nCreating an array of size %i...\n", daysBetween);
    date calendar[daysBetween];
    printf("Size of calendar: %i\n", ((sizeof calendar)/(sizeof calendar[0])));
    size = (sizeof calendar) / (sizeof calendar[0]);
    printf("\nPopulating calendar...\n");
    populateCalendar(calendar, counter, size);
    //------------
    int i = 0;
    for (i=0; i < daysBetween; i++){
        printf("Day is %i/%i/%i. hoursFree: %lf\n", calendar[i].day, calendar[i].month, calendar[i].year, calendar[i].hoursFree);
    }
    //------------
    printf("\nDeducting modules from hoursFree, after setting hoursFree to the given daily hours...\n");
    deductModulesFromHoursFree(calendar, size);
    //------------
    for (i=0; i < daysBetween; i++){
        printf("Day is %i/%i/%i. hoursFree: %lf\n", calendar[i].day, calendar[i].month, calendar[i].year, calendar[i].hoursFree);
    }
    //------------
    printf("\nDeducting assignments from hoursFree...\n");
    result = deductAssignmentsFromHoursFree(calendar, size);
    printf("\nResult after deductAssignmentsFromHoursFree: %i\n", result); //TESTING PURPOSES. REMEMBER TO REMOVE!
    return result;
}
