#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dbManager.h"

void readyState(),
     findCommand(char),
     assignments(),
     schedule(),
     logOut();

void login();

int userID = 0;
int loginID = 0;
int lineLoc = 0;



void printSchedule (){

}

void writeLog (char string[], int currentDate, int affectedDate){

}

void login(void){
  char testInput[MAX_LINE_LENGTH];
  char password[20];
  char string[100];
  char databaseSelect[100] = "users.txt";
  char search[100] = "USERS";
  char tempDB[100][100];
  char tempUserID[100][MAX_LINE_LENGTH];
  char usernameAndPassword[100][MAX_LINE_LENGTH];
  char tempLoginID[100][MAX_LINE_LENGTH];
  int userFound = 1;


  printf("\nEnter username: ");
  scanf("%s", &testInput);
  printf("\nEnter password: ");
  scanf("%s", &password);

  strcat(testInput, "_");
  strcat(testInput, password);

  // printf("\n%s", testInput);



  findSection(search, databaseSelect, &locOne, &locTwo);

  readSection(locOne, locTwo, tempDB, databaseSelect);
  // for (int i = 0; i < 10; i++) {
  //   printf("%s, i er = %i", tempDB[i], i);
  // }
  for (int i = locOne; i < locTwo; i++) {
    // printf("\nFUCK IAN");
    lineSplit(tempDB, &i, tempUserID, usernameAndPassword, tempLoginID);
    // printf("\n[%i] - %s", i, tempDB[i]);
    // printf("\n%i, uid = %s, uname = %s, loginID = %s", i, tempUserID[i], usernameAndPassword[i], tempLoginID[i]);
    userFound = strcmp(testInput, usernameAndPassword[i]);
    // printf("\nUserfound: %i", userFound );
    if (userFound == 0) {
      userID = atoi(tempUserID[i]);
      loginID = atoi(tempLoginID[i]);
      // printf("\nUserID: %i og loginID: %i", userID, loginID);
      userFound = 1;

    }

  }

  // findLine(string, &lineLoc, testInput, &locOne, databaseSelect);
  // printf("%i", lineLoc);



}

void readyState(){
    char command;
    while (loginID != 0) {
        printf("\nEnter command here: ");
        scanf(" %c", &command);
        findCommand(command);

    }
}

void findCommand(char command){
    switch (command){
    case 'a':
    case 'A':
        assignments();
        break;
    case 's':
    case 'S':
        schedule();
        break;
    case 'l':
    case 'L':
        logOut();
     default:
        break;
    }
}

void assignments(/* arguments */) {
  /* code */
}

void schedule(/* arguments */) {
  /* code */
}

void logOut(){
  loginID = 0;

}
