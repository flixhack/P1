#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dbManager.h"
#include "functions.h"
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
        int daysInCurrentMonth = daysInMonth(counter.month, counter.year);
        while (counter.day <= daysInCurrentMonth && i != (size)){
            calendar[i].year = counter.year;
            calendar[i].month = counter.month;
            calendar[i].day = counter.day;
            calendar[i].hoursFree = DAILY_SCHOOL_HOURS + 0.0;
            i++;
            counter.day++;
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
    int i = 0;
    int k = 0;
    for (i = 0; i < size; i++){
        dateToString(calendar, i, string);
        findSection(string, "calendar.txt", &locOne, &locTwo);
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
                    calendar[i].hoursFree -= ((duration + 0.0) / 60.0);
                }
            }
        }
    }
}

date stringToDate(char string[], char separator){
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
            dayNumCount++;
        }
        else if (string[k] != separator && parseSwitch == 2) {
            month[monthNumCount] = string[k];
            monthNumCount++;
        }
        else if (string[k] != separator && parseSwitch == 3) {
            year[yearNumCount] = string[k];
            yearNumCount++;
        }
    }
    day[dayNumCount] = '\0';
    month[monthNumCount] = '\0';
    year[yearNumCount] = '\0';
    date.day = atoi(day);
    date.month = atoi(month);
    date.year = atoi(year);


    return date;
}

date scanForEarliestAssignmentDate(char databaseSelect[]){
    date earliestAssDate;
    FILE *readFile = fopen(databaseSelect, "r");
    if (readFile == NULL){
        printf("Database file not found. Contact an administrator\n");
        exit(EXIT_FAILURE);
    }
    int lineCount = countLines(databaseSelect);
    char tempDB[lineCount][MAX_LINE_LENGTH];
    char entryTime[lineCount][100], entryDuration[lineCount][100], entryType[lineCount][4], entrySubject[lineCount][100], endDate[lineCount][10];

    readSection(-1, lineCount, tempDB, databaseSelect);
    int k;
    for (k = 0; k < lineCount + 1; k++) {
        calendarSplit(tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
    }
    int j;
    int earliestDate = 100000000;
    for (j = 0; j < lineCount; j++){
        if (containsChar(tempDB[j], '-') == 1) {
            date tempDate = stringToDate(endDate[j], '-');
            if (tempDate.year * 10000 + tempDate.month * 100 + tempDate.day < earliestDate) {
                earliestDate = tempDate.year * 10000 + tempDate.month * 100 + tempDate.day;
                earliestAssDate.day = tempDate.day;
                earliestAssDate.month = tempDate.month;
                earliestAssDate.year = tempDate.year;
            }
        }
    }
    return earliestAssDate;
}

int calcAssignmentWorkLoad(const int i, date calendar[], char entryType[][4], char entryDuration[][MAX_LINE_LENGTH], char endDate[][10]){
    int k;
    int j;
    int daysBetween;
    int fitsEasy = 0;
    date compareDateStart;
    double averageTime;
    double durationDouble;
    for (k = 0; k < (locTwo - locOne -1); k++){
        int test = strcmp(entryType[k], "ass");
        if (test == 0){
            compareDateStart = stringToDate(endDate[k], '-');
            printf("endDate[%i]: %s\n", k, endDate[k]);
            durationDouble = (atoi(entryDuration[k])) / 60.0;
            daysBetween = daysBetweenDates(compareDateStart, calendar[i]) - 2;
            printf("compareDateStart: %i/%i/%i. calendar[i]: %i/%i/%i\n", compareDateStart.day, compareDateStart.month, compareDateStart.year, calendar[i].day, calendar[i].month, calendar[i].year);
            averageTime = (durationDouble / daysBetween);
            fitsEasy = 1;
            //printf("calendar[%i].hoursFree = %lf, averageTime: %lf", j, calendar[j].hoursFree, averageTime);
            for (j = (i - daysBetween); j < i && fitsEasy != 0; j++){
                if (calendar[j].hoursFree < averageTime){
                    fitsEasy = 0;
                }
            }
            if (fitsEasy == 1){
                for (j = (i - daysBetween); j < i; j++){
                    calendar[j].hoursFree -= averageTime;
                }
            }
            else {
                double accumulator = 0.0;
                for (j = (i - daysBetween); j < i; j++){
                    accumulator += calendar[j].hoursFree;
                }
                durationDouble = (atoi(entryDuration[k]) / 60.0);
                if (accumulator >= durationDouble){
                    for (j = (i - daysBetween); j < i; j++){
                        durationDouble -= calendar[j].hoursFree;
                        if (durationDouble < 0){
                            calendar[j].hoursFree = (durationDouble * -1);
                        }
                        else {
                            calendar[j].hoursFree = 0;
                        }
                    }
                }
                else {
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
    int returnValue = 1;
    for (i = 0; i < size && returnValue != 0; i++){
        dateToString(calendar, i, string);
        printf("Date: %s\n", string);
        findSection(string, "calendar.txt", &locOne, &locTwo);
        if (locOne != 0 && locTwo != 0){
            readSection(locOne, locTwo, tempDB, "calendar.txt");
            //------
            for (k = 0; k < (locTwo - locOne -1); k++){
                printf("%s\n", tempDB[k]);
            }
            //------
            for (k = 0; k < (locTwo - locOne -1); k++){
                printf("tempDB[%i] foer: %s\n", k, tempDB[k]);
                calendarSplit (tempDB, k, entryTime, entryDuration, entryType, entrySubject, endDate);
                printf("tempDB[%i] efter: %s\n", k, tempDB[k]);
                printf("entryTime[k]: %s, entryDuration[k]: %s, entryType[k]: %s, entrySubject[k]: %s, endDate[k]: %s\n", entryTime[k], entryDuration[k], entryType[k], entrySubject[k], endDate[k]);
            }
            printf("Entering calcAssignmentWorkLoad with i: %i\n", i);
            returnValue = calcAssignmentWorkLoad(i, calendar, entryType, entryDuration, endDate);
        }
    }
    return returnValue;
}

int calcPrimaryAssWorkLoad(date calendar[], int size, element assignment){
    int startingPoint;
    int i = 0;
    int run = 1;
    int daysBetween;
    daysBetween = daysBetweenDates(assignment.startDate, assignment.endDate);
    while (run == 1 && i < size){
        if (calendar[i].year == assignment.startDate.year && calendar[i].month == assignment.startDate.month && calendar[i].day == assignment.startDate.day){
            startingPoint = i;
            run = 0;
        }
        i++;
    }
    double totalHours;
    totalHours = (assignment.duration + 0.0) / (60.0);
    for (i = startingPoint; i < startingPoint + daysBetween - 2 && totalHours > 0; i++){
        totalHours -= calendar[i].hoursFree;
    }
    if (totalHours >= 0){
        return 0;
    }
    else {
        return 1;
    }
}

int calcWorkLoad(element newElement){
    int result = 0;
    int daysBetween = 0,
        size = 0;
    date earliestDate;
    date *calendar;
    earliestDate = scanForEarliestAssignmentDate("calendar.txt");
    date latestDate;
    latestDate = findLatestDate("calendar.txt");
    date counter = earliestDate;
    daysBetween = daysBetweenDates(earliestDate, latestDate);
    // date calendar[daysBetween];
    calendar = (date *) calloc(daysBetween, sizeof(date));
    size = (sizeof calendar) / (sizeof calendar[0]);
    populateCalendar(calendar, counter, size);
    deductModulesFromHoursFree(calendar, size);
    result = deductAssignmentsFromHoursFree(calendar, size);
    if (result == 0){
        return 0;
    }
    result = calcPrimaryAssWorkLoad(calendar, size, newElement);
    return result;
    free(calendar);
}
