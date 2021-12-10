#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "dbManager.h"
#define MAX_LINE_LENGTH 100

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

void populateCalendar(date calendar[], date startDate){
    int i = 0;
    date counter = startDate;
    int run = 1;
    while (run == 1){
    int daysInCurrentMonth = daysInMonth(counter.month, counter.year);
        while (counter.day <= daysInCurrentMonth){
            calender[i].year = counter.year;
            calender[i].month = counter.month;
            calender[i].day = counter.day;
            i++;
            counter.day++;
        }
    counter.day = 1;
    if (counter.month == 12){
        counter.month = 1;
        counter.year++;
    }
    else {
        counter.month++;
    }
    if (i == (sizeof calendar[]) / (sizeof calendar[0])){
        run = 0;
    }
}

void calcHoursFree(date calendar[]){

}

double calcWorkLoad(element newElement){
    double result = 0;
    date counter = newElement.startDate;
    int daysInCurrentMonth = 0;
    switch (newElement.type){
        case 1: ;//Module
            result = newElement.duration / 60;
            break;
        case 2: //Assignment
        case 3: //Homework
        case 4: //Test
            int daysBetween = 0;
            daysBetween = daysBetweenDates(newElement.startDate, newElement.endDate);
            date calendar[daysBetween];
            populateCalendar(calendar, counter)
            break;
        default: ;
            break;
    }
    printf("Calculated workload: %lf\n", result); //TESTING PURPOSES. REMEMBER TO REMOVE!
    return result;
}
