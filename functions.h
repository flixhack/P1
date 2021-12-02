#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readyState(int),
     findCommand(char),
     assignments(userID, loginID),
     schedule(userID, loginID),
     logOut();

int login();

int loggedIn = 0;

void writeLog (char string[], int currentDate, int affectedDate){

}

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

void readyState(int loginVar){
    char command;
    while (loggedIn != 0) {
        printf("\nEnter command here: ");
        scanf(" %c", &command);
        findCommand(command);

    }
}

void findCommand(char command){
    switch (command){
    case 'a':
    case 'A':
        assignments(userID, loginID);
        break;
    case 's':
    case 'S':
        schedule(userID, loginID);
        break;
    case 'l':
    case 'L':
        logOut();
     default:
        break;
    }
}

void assignments(int userID, int loginID) {
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 2 || loginID == 3){
      printf("Do you wish to see current assignments, go to the assignment editor, or go back? (C/E/B)");
      scanf("%c", &command);
      switch (command){
        case 'c':
        case 'C':
        printAssignments(userID, loginID);
        break;
        case 'e':
        case 'E':
        assignmentEditor(userID, loginID);
        break;
        case 'b':
        case 'B':
        run = 0;
        break;
      }
    }
    else printAssignments(userID, 1);
  }
}

void printAssignments(int userID, int LoginID){

}

void assignmentEditor(int userID, int LoginID){
  int run = 1;
  char command;
  while (run == 1){
    printf("Create an assignment, edit an assignment, delete an assignment or go back? (C/E/D/B)");
    scanf("%c", &command);
    switch (command)
    {
    case 'c':
    case 'C':
      
      break;
    case 'e':
    case 'E':

      break;
    case 'd':
    case 'D':

      break;
    case 'b':
    case 'B':
      run = 0;
      break;
    default:
        break;
    }  
  }
}

void schedule(int userID, int loginID) {
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 3){
      printf("Do you wish to see the schedule, go to the schedule editor, or go back? (C/E/B)");
      scanf("%c", &command);
      switch (command){
        case 'c':
        case 'C':
        printSchedule(userID, loginID);
        break;
        case 'e':
        case 'E':
        scheduleEditor(userID);
        break;
        case 'b':
        case 'B':
        run = 0;
        break;
      }
    }
    else printSchedule(userID, 1);
  }
}

void printSchedule (int userID, int loginID){

}

void scheduleEditor(int userID){
  int run = 1;
  char command;
  while (run == 1){
    printf("Create a module, Edit a module, delete a module or go back? (C/E/D/B)");
    scanf("%c", &command);
    switch (command)
    {
    case 'c':
    case 'C':
      
      break;
    case 'e':
    case 'E':

      break;
    case 'd':
    case 'D':
      
      
      break;
    case 'b':
    case 'B':
      run = 0;
      break;
    default:
    
    }  
  }
}

void logOut(){
  loggedIn = 0;

}
