#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dbManager.h"
#include "structs.h"
#define MAX_LINE_LENGTH 100

struct date{
    int week;
    int day;
    int month;
    int year;
    double hoursFree;
};
typedef struct date date;

struct element{
    date date;
    char time[6];   //determines start- or end-time. 1930 = 19:30
    int duration;    //Antal minutter
    char subject[MAX_LINE_LENGTH]; 
    int type; //1: Module, 2: Assignment, 3: Homework, 4: Test
};
typedef struct element element;

void readyState(int),
     findCommand(char, int),
     assignments(int),
     schedule(int),
     printSchedule(int),
     scheduleEditor(int),
     logOut(),
     printAssignments(int),
     callDatabase(char, char*, int, char*),
     assignmentEditor(int);

int login();

int loggedIn = 0;
int userID = 1;

int main(){

  int loginID = login();
  readyState(loginID);  
}
double calcWorkLoad(element);

int login(void){
    char loginScan;
    printf("\nEnter your username (T, S, A): ");
    scanf("%c", &loginScan);
    switch (loginScan){
    case 's':
    case 'S':
        loggedIn = 1;
        break;
    case 't':
    case 'T':
        loggedIn = 2;
        break;
    case 'a':
    case 'A':
        loggedIn = 3;
        break;
    default:
        break;
    }
    printf("\nYou are logged in as %d", loggedIn );
    return(loggedIn);
}

void readyState(int loginID){
    char command;
    while (loginID != 0) {
        printf("\nEnter command here: ");
        scanf(" %c", &command);
        findCommand(command, loginID);
    }
}

void findCommand(char command, int loginID){
    switch (command){
    case 'a':
    case 'A':
        assignments(loginID);
        break;
    case 's':
    case 'S':
        schedule(loginID);
        break;
    case 'l':
    case 'L':
        logOut();
     default:
        break;
    }
}

void assignments(int loginID) {
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 2 || loginID == 3){
      printf("Do you wish to see current assignments, go to the assignment editor, or go back? (C/E/B)");
      scanf("%c", &command);
      switch (command){
        case 'c':
        case 'C':
        printAssignments(loginID);
        break;
        case 'e':
        case 'E':
        assignmentEditor(loginID);
        break;
        case 'b':
        case 'B':
        run = 0;
        break;
        default:
        printf("Not a valid command.\n");
        break;
      }
    }
    else printAssignments(loginID);
  }
}

void printAssignments(int LoginID){

}

void assignmentEditor(int LoginID){
  int run = 1;
  char mode, command;
  char database[MAX_LINE_LENGTH] = "calendar.txt";
  while (run == 1){
    printf("Create an assignment, edit an assignment, delete an assignment or go back? (C/E/D/B)");
    scanf("%c", &command);
    mode = command;
    switch (command)
    {
    case 'c':;
    case 'C':;
      date newDate;
      element newAssignment;
      newAssignment.date = newDate;
      newAssignment.type = 1;
      break;
    case 'e':;
    case 'E':;

      break;
    case 'd':
    case 'D':

      break;
    case 'b':
    case 'B':
      run = 0;
      break;
    default:
        printf("Not a valid command.\n");
      break;
      
    }  
  }
}

void schedule(int loginID) {
  
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 3){
      printf("Do you wish to see the schedule, go to the schedule editor, or go back? (S/E/B): ");
      scanf(" %c", &command);
      switch (command){
        case 's':
        case 'S':
        printSchedule(loginID);
        break;
        case 'e':
        case 'E':
        scheduleEditor(loginID);
        break;
        case 'b':
        case 'B':
        run = 0;
        break;
        default:
        printf("Not a valid command.\n");
        break;
      }
    }
    else printSchedule(loginID);
  }
}

void printSchedule (int loginID){
 
}

void scheduleEditor(int userID){
  char mode, x;
  char database[MAX_LINE_LENGTH] = "calendar.txt", tempTime[MAX_LINE_LENGTH];
  char endTime[MAX_LINE_LENGTH], newLine[MAX_LINE_LENGTH];
  int run = 1, lineLoc = 0;
  char command;
  while (run == 1){
    printf("\nCreate a module, Edit a module, delete a module or go back? (C/E/D/B): ");
    scanf(" %c", &command);
    mode = command;
    switch (command)
    {
    case 'c':;
    case 'C':;
      date newDate;
      element newModule;
      newModule.date = newDate;
      newModule.type = 1;
        printf("Insert a day (DD), month (MM) and a year (YYYY) for the module to take place: ");
        scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);
        sprintf(tempTime, "%d/%d/%d", newDate.day, newDate.month, newDate.year);

        findSection(tempTime, database, &locOne, &locTwo);

        if (locTwo == -1){
          locTwo = countLines(database);
          callDatabase(mode, database, locTwo, tempTime);
          sprintf(endTime, "%s_END", tempTime);
          callDatabase(mode, database, locTwo + 1, endTime);
          locTwo = -1;
          findSection(tempTime, database, &locOne, &locTwo);
        }
        
        printf("Insert the starting time (Hours:Minutes), duration (in minutes) and module: ");

        scanf("%s %d %s", &newModule.time, &newModule.duration, newModule.subject);
        
        printf("Is this module correct? (y/n)\n\n");
        printf("Module: %s Date: %d/%d/%d   Duration: %d   Time: %s\n", newModule.subject, newDate.day, newDate.month, newDate.year, newModule.duration, newModule.time);
        scanf(" %c", &x);

        if(x == 'y'){
          sprintf(newLine, "%s_%d_%d_%s", newModule.time, newModule.duration, newModule.type, newModule.subject);
          //if(calcWorkLoad() >= 0){
            callDatabase(mode, database, locOne + 1, newLine);
          //}
          //else printf("No more hours available to create module.\n");
          break;
        }
        else break;
    case 'e':;
    case 'E':;
      date editDate;
      char searchTerm[MAX_LINE_LENGTH], tempDb[MAX_LINE_LENGTH];
      printf("Choose a date from which you wish to edit a module: ");
      scanf("%d %d %d", &editDate.day, &editDate.month, &editDate.year);
      sprintf(tempTime, "%d/%d/%d", editDate.day, editDate.month, editDate.year);

      printf("These are the modules for the given date:\n");
      readSection(locOne, locTwo, &tempDb, database);
      
      printf("Input the time of the module that you wish to edit: ");
      scanf(" %s", searchTerm);
      lineLoc = findLineLoc(searchTerm, locOne, database);
      
      callDatabase(mode, database, lineLoc, newLine);

    case 'd':;
    case 'D':;
      date deleteDate;
      int tempTime;
        printf("Choose a date from which you wish to delete a module: ");
        scanf("%d %d %d", &deleteDate.day, &deleteDate.month, &deleteDate.year);
        printf("These are the modules for the given date:\n");
        
        printf("Please enter the time for the Module that you wish to delete: ");
        scanf("%d", &tempTime);
        printf("Confirm? (y/n): ");

      break;
    case 'b':
    case 'B':
      run = 0;
      break;
    default:
      printf("Not a valid command.\n");
      break;
    }  
  }
}

void callDatabase(char mode, char *database, int lineNum, char *newLine){
    databaseEdit(&mode, &lineNum, newLine, database);
}

void logOut(){
  loggedIn = 0;

}
