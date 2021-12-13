#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_LENGTH 100
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
        printf("Days in current month: %i\n", daysInCurrentMonth);
        printf("counter.day: %i\n", counter.day);
        printf("i: %i\n", i);
        printf("Size of calendar: %i\n", (size));
        while (counter.day <= daysInCurrentMonth && i != (size)){
            calendar[i].year = counter.year;
            calendar[i].month = counter.month;
            calendar[i].day = counter.day;
            i++;
            counter.day++;
            printf("Populated one element with a date\n"); //TESTING
        }
        counter.day = 1;
        if (counter.month == 12){
            counter.month = 1;
            counter.year++;
        }
        else {
            counter.month++;
        }
        if (i == size){
            run = 0;
        }
    }
}

void dateToString(date calendar[], int i, char string[]){
    sprintf(string, "%i/%i/%i\n", calendar[i].day, calendar[i].month, calendar[i].year);
    printf("Day: %i\n", calendar[i].day); //TESTING
}

void calcHoursFree(date calendar[]){

}

void readDB(date calendar[], int size){
    char tempDB[100][MAX_LINE_LENGTH];
    char entryTime[100][MAX_LINE_LENGTH];
    char entryDuration[100][MAX_LINE_LENGTH];
    char entryType[100][4];
    char entrySubject[100][MAX_LINE_LENGTH];
    char string[10];
    int lineLoc;
    int locOne;
    int locTwo;
    int i = 0;
    int k = 0;
    for (i = 0; i <= size; i++){
        calendar[0].hoursFree = DAILY_SCHOOL_HOURS;
        dateToString(calendar, i, string);
        printf("%s", string); //TESTING
        findSection(string, "calendar.txt", &locOne, &locTwo);
        readSection(locOne, locTwo, tempDB[][100], "calendar.txt");
        for (k = 0; k <= (locTwo - locOne); k++){
            calendarSplit (tempDB[][100], k, entryTime[][MAX_LINE_LENGTH], entryDuration[][MAX_LINE_LENGTH], entryType[][4], entrySubject[][MAX_LINE_LENGTH]);
        }
    }
}

double calcWorkLoad(element newElement){
    double result = 0;
    date counter = newElement.startDate;
    int daysBetween = 0,
        size = 0;
    daysBetween = daysBetweenDates(newElement.startDate, newElement.endDate);
    date calendar[daysBetween];
    printf("Size of calendar: %i\n", ((sizeof calendar)/(sizeof calendar[0])));
    size = (sizeof calendar) / (sizeof calendar[0]);
    populateCalendar(calendar, counter, size);
    readDB(calendar, size);
    printf("Calculated workload: %lf\n", result); //TESTING PURPOSES. REMEMBER TO REMOVE!
    return result;
}
