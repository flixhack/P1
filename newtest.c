#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "C:/Users/m/Desktop/P1/P1/structs.h"
#include "calendarnew.h"
//#include "C:/Users/m/Desktop/P1/P1/functions.h"
//#include "C:/Users/m/Desktop/P1/P1/dbManager.h"




int main(void){
  // element assignment;
  // assignment.startDate.day = 1;
  // assignment.startDate.month = 2;
  // assignment.startDate.year = 2012;
  // assignment.endDate.day = 25;
  // assignment.endDate.month = 2;
  // assignment.endDate.year = 2012;
  date date;
  date = scanForEarliestAssignmentDate();
  printf("Earliest assignment was given on: %i/%i/%i\n", date.day, date.month, date.year);
  return 0;
}