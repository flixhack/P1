#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readyState(),
     findCommand(char),
     assignments(),
     schedule(),
     printSchedule(),
     scheduleEditor(),
     logOut(),
     printAssignments(),
     callDatabase(char, char*, int, char*),
     assignmentEditor(),
     login();
int calcWorkLoad(element);

int userID = 0;
int loginID = 0;
int lineLoc = 0;


void printTime(char *string, int time){ //must recieve a array of size 5
    char timeCode[4];
    if (time > 999){
        sprintf(timeCode, "%i", time);
        string[0] = timeCode[0];
        string[1] = timeCode[1];
        string[2] = ':';
        string[3] = timeCode[2];
        string[4] = timeCode[3];
    }
    else if (time < 1000 && time > 99){
        sprintf(timeCode, "%i", time);
        string[0] = '0';
        string[1] = timeCode[0];
        string[2] = ':';
        string[3] = timeCode[1];
        string[4] = timeCode[2];
    }
    else if (time < 100 && time > 9){
        sprintf(timeCode, "%i", time);
        string[0] = '0';
        string[1] = '0';
        string[2] = ':';
        string[3] = timeCode[0];
        string[4] = timeCode[1];
    }
    else if (time < 10){
        sprintf(timeCode, "%i", time);
        string[0] = '0';
        string[1] = '0';
        string[2] = ':';
        string[3] = '0';
        string[4] = timeCode[0];
    }
    for (int i = 0; i < 5; i++){
        printf("%c", string[i]);
    }
}  //Recieve a stored int and print it as a time stamp. Example: int == 945 becomes 9:45

void login(void){
  char testInput[MAX_LINE_LENGTH];
  char password[20];
  char databaseSelect[100] = "users.txt";
  char search[100] = "USERS";
  char tempDB[100][100];
  char tempUserID[100][MAX_LINE_LENGTH];
  char usernameAndPassword[100][MAX_LINE_LENGTH];
  char tempLoginID[100][MAX_LINE_LENGTH];
  int userFound = 1;


  printf("\nEnter username: ");
  scanf("%s", testInput);
  printf("\nEnter password: ");
  scanf("%s", password);

  strcat(testInput, "_");
  strcat(testInput, password);

  findSection(search, databaseSelect, &locOne, &locTwo);

  readSection(locOne, locTwo, tempDB, databaseSelect);
  for (int i = locOne; i < locTwo; i++) {
    lineSplit(tempDB, &i, tempUserID, usernameAndPassword, tempLoginID);
    userFound = strcmp(testInput, usernameAndPassword[i]);
    if (userFound == 0) {
      userID = atoi(tempUserID[i]);
      loginID = atoi(tempLoginID[i]);
      userFound = 1;
    }
  }
}

void readyState(){
    char command;
    while (loginID != 0) {
        printf("\nEnter command here (press h for help): ");

        scanf(" %c", &command);
        findCommand(command);
    }
}

void findCommand(char command){
    switch (command){
    case 'h':
    case 'H':
    printf("List of Commands:\n");
    printf("A = Assignments\n");
    printf("S = Schedule\n");
    printf("L = Log Out:\n");
    break;
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
      break;
    default:
      printf("Command not Found\n");
      break;
    }
}

void assignments() {
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 2 || loginID == 3){
      printf("Do you wish to see current assignments, go to the assignment editor, or go back? (C/E/B)");
      scanf(" %c", &command);
        switch (command){
          case 'c':
          case 'C':
          printAssignments();
          break;
          case 'e':
          case 'E':
          assignmentEditor();
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
      else printAssignments();
  }
}

void printAssignments(){

}

void assignmentEditor(){
  int run = 1;
  char mode, command, editCondition;
  char database[MAX_LINE_LENGTH] = "calendar.txt", tempDate[MAX_LINE_LENGTH];
  char endTime[MAX_LINE_LENGTH], newLine[MAX_LINE_LENGTH];
  time_t current = time(NULL);
  struct tm tm = *localtime(&current);
  while (run == 1){
    printf("\nCreate an assignment, edit an assignment, delete an assignment or go back? (C/E/D/B): ");
    scanf(" %c", &command);
    mode = command;
    switch (command)
    {
    case 'c':;
    case 'C':;
      date handIn;
      date handOut;
      element newAssignment;
      handOut.day = tm.tm_mday;
      handOut.month = tm.tm_mon + 1;
      handOut.year = tm.tm_year + 1900;
      newAssignment.endDate = handIn;
      newAssignment.startDate = handOut;
      newAssignment.type = 2;
        printf("Insert a day (DD), month (MM) and a year (YYYY) for the assignment to take place: ");
        scanf("%d %d %d", &handIn.day, &handIn.month, &handIn.year);
        sprintf(tempDate, "%d/%d/%d", handIn.day, handIn.month, handIn.year);
        if(handIn.year < (tm.tm_year + 1900)){
          printf("Can't make an assignment in the past.");
          break;
        }
        if(handIn.month < (tm.tm_mon + 1) && handIn.year == (tm.tm_year + 1900)){
          printf("Can't make an assignment in the past.");
          break;
        }
        if (handIn.day < (tm.tm_mday) && handIn.month == (tm.tm_mon + 1) && handIn.year == (tm.tm_year + 1900)){
          printf("Can't make an assignment in the past.");
          break;
        }
        else findSection(tempDate, database, &locOne, &locTwo);

        if(locTwo == 0){
          printf("Date not found, creating new date in database.\n");
          callDatabase(mode, database, locTwo + 1, tempDate);
          sprintf(endTime, "%s_END", tempDate);
          callDatabase(mode, database, locTwo + 2, endTime);
          locTwo = 0;
          findSection(tempDate, database, &locOne, &locTwo);
        }

        printf("Insert the starting time (Hours:Minutes), duration (in minutes) and subject: ");

        scanf("%s %d %s", newAssignment.time, &newAssignment.duration, newAssignment.subject);

        printf("Is this assignment correct? (y/n)\n\n");
        printf("Subject: %s Date: %d/%d/%d   Duration: %d   Time: %s\n", newAssignment.subject, handIn.day, handIn.month, handIn.year, newAssignment.duration, newAssignment.time);
        scanf(" %c", &editCondition);

        if(editCondition == 'y'){
          sprintf(newLine, "%s_%i_ass_%s_%i-%i-%i", newAssignment.time, newAssignment.duration, newAssignment.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
          int fits;
          fits = calcWorkLoad(newAssignment);
          if(fits > 0){
            callDatabase(mode, database, locOne + 1, newLine);
          }
          else printf("No more hours available to create assignment.\n");
          break;
        }
        else break;
    case 'e':;
    case 'E':;
      printf("The function editAssignment is not yet implemented\n");
      break;
    case 'd':;
    case 'D':;
      printf("The function deleteAssignment is not yet implemented\n");
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
void schedule() {

  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 3){
      printf("Do you wish to see the schedule, go to the schedule editor, or go back? (S/E/B): ");
      scanf(" %c", &command);
      switch (command){
        case 's':
        case 'S':
        printSchedule();
        break;
        case 'e':
        case 'E':
        scheduleEditor();
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
    else printSchedule();
  }
}

void printSchedule (){
  printf("The function printSchedule is not yet implemented\n");
}

void scheduleEditor(){
  char mode, x;
  char database[MAX_LINE_LENGTH] = "calendar.txt", tempTime[MAX_LINE_LENGTH];
  char endTime[MAX_LINE_LENGTH], newLine[MAX_LINE_LENGTH];
  int run = 1;
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
      newModule.endDate = newDate;
      newModule.type = 1;
        printf("Insert a day (DD), month (MM) and a year (YYYY) for the module to take place: ");
        scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);
        sprintf(tempTime, "%d/%d/%d", newDate.day, newDate.month, newDate.year);

        findSection(tempTime, database, &locOne, &locTwo);

        if (locTwo == -1 || locTwo == 0){
          locTwo = countLines(database);
          callDatabase(mode, database, locTwo, tempTime);
          sprintf(endTime, "%s_END", tempTime);
          callDatabase(mode, database, locTwo + 1, endTime);
          locTwo = -1;
          findSection(tempTime, database, &locOne, &locTwo);
        }

        printf("Insert the starting time (Hours:Minutes), duration (in minutes) and module: ");

        scanf("%s %d %s", newModule.time, &newModule.duration, newModule.subject);

        printf("Is this module correct? (y/n)\n\n");
        printf("Module: %s Date: %d/%d/%d   Duration: %d   Time: %s\n", newModule.subject, newDate.day, newDate.month, newDate.year, newModule.duration, newModule.time);
        scanf(" %c", &x);

        if(x == 'y'){
          sprintf(newLine, "%s_%i_mod_%s", newModule.time, newModule.duration, newModule.subject);
          callDatabase(mode, database, locOne + 1, newLine);
          break;
        }
        else break;
    case 'e':;
    case 'E':;
      printf("The function editModule is not yet implemented\n");
      break;

    case 'd':;
    case 'D':;
      printf("The function deleteModule is not yet implemented\n");
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
  loginID = 0;

}
