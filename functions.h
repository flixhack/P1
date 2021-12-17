#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dbManager.h"
#include "structs.h"

enum types {mod = 1, ass}; typedef enum types types;


void readyState(),
     findCommand(char),
     assignments(int),
     schedule(int),
     printSchedule(),
     scheduleEditor(int),
     logOut(),
     printAssignments(int),
     callDatabase(char, char*, int, char*),
     assignmentEditor(int),
     login();

int userID = 0;
int loginID = 0;
int lineLoc = 0;

int readTime(void){
    int n1 = 0;
    int n2 = 0;
    char col;
    scanf(" %i", &n1);
    scanf("%c", &col);
    if (col != ':'){
        return 0;
    }
    else if (n1 > 24 || n1 < 0){
        return 0;
    }
    else {
        scanf("%i", &n2);
    }
    if (n2 > 60 || n2 < 0){
        return 0;
    }
    else if (n1 == 0 && n2 == 0){
      return 2400;  // since 0 is the error value, a time  of 00:00  will instead be read as 24:00.
    }
    else {
        return n2 + n1 * 100;
    }
}

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

char* receiveString() {

// stolen: https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u

    printf("Enter string: ");

    char *string = NULL;
    int currentChar = 0, sizeCounter = 1, c;
    string = (char *)malloc(sizeof(char));

    //error checking
    if (string == NULL) { //hvis der ikke er blevet indtastet noget er string == NULL
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    while((c = getc(stdin)) && c != '\n')
    {
        string[currentChar] = c;
        string = realloc(string,sizeCounter * sizeof(char));

// printf(" string2: %s", string);

        //error checking
        if (string == NULL) {
            printf("Error allocating memory\n");
            free(string);
            exit(EXIT_FAILURE);
        }
// printf(" string1s: %s", string);
        sizeCounter++;
        currentChar++;
    }
    string[currentChar] = '\0';

    printf(" string: %s", string);

    return string;

    /* det vil være muligt at have en char* i main for at
    opbevare værdien for return af receiveString og derefter free() efter når den ikke bruges */
}

void writeLog (int currentDate, int affectedDate){

}

void login(void){
  char testInput[MAX_LINE_LENGTH];
  char password[20];
  // char string[100];
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
    else printf("User not found, terminating program...");
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
      assignments(loginID);
      break;
    case 's':
    case 'S':
      schedule(loginID);
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

void assignments(int loginID) {
  int run = 1;
  char command;
  while (run == 1){
    if (loginID == 2 || loginID == 3){
      printf("Do you wish to see current assignments, go to the assignment editor, or go back? (C/E/B)");
      scanf(" %c", &command);
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
          sprintf(newLine, "%s_%d_ass_%s_%d-%d-%d", newAssignment.time, newAssignment.duration, newAssignment.type, newAssignment.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
          //if(calcWorkLoad() >= 0){
            callDatabase(mode, database, locOne + 1, newLine);
          //}
          //else printf("No more hours available to create assignment.\n");
          break;
        }
        else break;
    case 'e':;
    case 'E':;
      printf("The function editAssignment is not yet implemented\n");
      /* date editDate;
      element editAssignment;
      int confirm;
      char searchTerm[MAX_LINE_LENGTH], tempDb[MAX_LINE_LENGTH];
      char stringDuration[MAX_LINE_LENGTH], stringType[4],
           stringSubject[MAX_LINE_LENGTH], stringTime[MAX_LINE_LENGTH],
           printer[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
      printf("Choose a date from which you wish to edit an assignment: ");
      scanf("%d %d %d", &editDate.day, &editDate.month, &editDate.year);
      editAssignment.date = editDate;
      sprintf(tempDate, "%d/%d/%d", editDate.day, editDate.month, editDate.year);
      findSection(tempDate, database, &locOne, &locTwo);
      if(locTwo == 0){
        printf("There is nothing listed under the given date");
      }
      readSection(locOne, locTwo, &tempDb, database);
      for(int i = 0; i <= locTwo - locOne; i++){
        calendarSplit(&tempDb, i, &stringTime, &stringDuration, &stringType, &stringSubject);
      }
      printf("Input the time of the assignment that you wish to edit (HH:MM): ");
      scanf(" %s", searchTerm);
      for(int j = 0; j <= locTwo - locOne; j++){
        confirm = strcmp(&stringType[j], "Ass");
        if(confirm == 0){
          confirm = strcmp(&stringTime[j], searchTerm);
          if (confirm == 0){
            int editLine = findLineLoc(searchTerm, locOne, database);
            printf("editline: %d\n", editLine);
            int duration = stringToInt(stringDuration);
            editCondition = 'x';
            printf("%c", editCondition);
            while(editCondition == 'x'){
              printf("Do you wish to edit the end date, hours set or subject? (E/D/S): ");
              scanf(" %c", &command);
              if(command == 'e' || command == 'E'){
                printf("\nPlease enter this assignment's new end date: ");
                scanf(" %s", editAssignment.time);
              }
              else if(command == 'd' || command == 'D'){
                printf("\nPlease enter the hours set for this assignment: ");
                scanf("%d", &duration);
              }

              else if(command == 's' || command == 'S'){
                printf("Please enter this assignment's new subject: ");
                scanf(" %s", editAssignment.subject);
              }
              else printf("Invalid edit parameter");

              printf("This is your current Assignment: Subject: %s Date: %d/%d/%d   Duration: %d   Time: %s.\n confirm module, edit further or cancel? (y/n/c)", editAssignment.subject, editDate.day, editDate.month, editDate.year, duration, editAssignment.time);
              scanf(" %c", &editCondition);
              if(editCondition == 'y'){
                sprintf(newLine, "%s_%d_%s_%s_%d-%d-%d", editAssignment.time, duration, stringType, editAssignment.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                callDatabase(mode, database, editLine, newLine);
              }
              else if(editCondition == 'n'){
                sprintf(newLine, "%s_%d_%s_%s_%d-%d-%d", editAssignment.time, duration, stringType, editAssignment.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                editCondition = 'x';
              }
              else if(editCondition == 'c'){
                while(editCondition != 'y' && editCondition != 'x'){
                  printf("Do you wish to exit editing this assignment? (y/n)");
                  if(editCondition == 'y'){

                  }
                  else if(editCondition == 'n'){
                    editCondition = 'x';
                  }
                  else printf("Invalid Command.");
                }
              }
            }
          locTwo = 0;
          }
        }
      } */
      break;
    case 'd':;
    case 'D':;
      printf("The function deleteAssignment is not yet implemented\n");
    /*  date deleteDate;
      int tempTime;
        printf("Choose a date from which you wish to delete an assignment: ");
        scanf("%d %d %d", &deleteDate.day, &deleteDate.month, &deleteDate.year);

        printf("Please enter the time for the Assignment that you wish to delete: ");
        scanf("%d", &tempTime);
        printf("Confirm? (y/n): ");
      */
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
  printf("The function printSchedule is not yet implemented\n");
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
      newModule.endDate = newDate;
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

        scanf("%s %d %s", newModule.time, &newModule.duration, newModule.subject);

        printf("Is this module correct? (y/n)\n\n");
        printf("Module: %s Date: %d/%d/%d   Duration: %d   Time: %s\n", newModule.subject, newDate.day, newDate.month, newDate.year, newModule.duration, newModule.time);
        scanf(" %c", &x);

        if(x == 'y'){
          sprintf(newLine, "%s_%d_mod_%s", newModule.time, newModule.duration, newModule.type, newModule.subject);
          //if(calcWorkLoad() >= 0){
            callDatabase(mode, database, locOne + 1, newLine);
          //}
          //else printf("No more hours available to create assignment.\n");
          break;
        }
        else break;
    case 'e':;
    case 'E':;
      printf("The function editModule is not yet implemented\n");
    /*  date editDate;
      date editDate;
      element editSchedule;
      int confirm;
      char searchTerm[MAX_LINE_LENGTH], tempDb[MAX_LINE_LENGTH];
      char stringDuration[MAX_LINE_LENGTH], stringType[4],
           stringSubject[MAX_LINE_LENGTH], stringTime[MAX_LINE_LENGTH],
           printer[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
      printf("Choose a date from which you wish to edit a module: ");
      scanf("%d %d %d", &editDate.day, &editDate.month, &editDate.year);
      editSchedule.date = editDate;
      sprintf(tempTime, "%d/%d/%d", editDate.day, editDate.month, editDate.year);
      findSection(tempTime, database, &locOne, &locTwo);
      if(locTwo == 0){
        printf("There is nothing listed under the given date");
      }
      readSection(locOne, locTwo, &tempDb, database);
      for(int i = 0; i <= locTwo - locOne; i++){
        calendarSplit(&tempDb, i, &stringTime, &stringDuration, &stringType, &stringSubject);
      }
      printf("Input the time of the module that you wish to edit (HH:MM): ");
      scanf(" %s", searchTerm);
      for(int j = 0; j <= locTwo - locOne; j++){
        confirm = strcmp(&stringType[j], "Ass");
        if(confirm == 0){
          confirm = strcmp(&stringTime[j], searchTerm);
          if (confirm == 0){
            int editLine = findLineLoc(searchTerm, locOne, database);
            printf("editline: %d\n", editLine);
            int duration = stringToInt(stringDuration);
            editCondition = 'x';
            printf("%c", editCondition);
            while(editCondition == 'x'){
              printf("Do you wish to edit the time, duration or subject? (T/D/S): ");
              scanf(" %c", &command);
              if(command == 't' || command == 'T'){
                printf("\nPlease enter this module's new time: ");
                scanf(" %s", editAssignment.time);
              }
              else if(command == 'd' || command == 'D'){
                printf("\nPlease enter this module's new duration: ");
                scanf("%d", &duration);
              }

              else if(command == 's' || command == 'S'){
                printf("Please enter this module's new subject: ");
                scanf(" %s", editAssignment.subject);
              }
              else printf("Invalid edit parameter");

              printf("This is your current Module: Subject: %s Date: %d/%d/%d   Duration: %d   Time: %s.\n confirm module, edit further or cancel? (y/n/c)", editAssignment.subject, editDate.day, editDate.month, editDate.year, duration, editAssignment.time);
              scanf(" %c", &editCondition);
              if(editCondition == 'y'){
                sprintf(newLine, "%s_%d_%s_%s_%d-%d-%d", editSchedule.time, duration, stringType, editSchedule.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                callDatabase(mode, database, editLine, newLine);
              }
              else if(editCondition == 'n'){
                sprintf(newLine, "%s_%d_%s_%s_%d-%d-%d", editSchedule.time, duration, stringType, editSchedule.subject, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                editCondition = 'x';
              }
              else if(editCondition == 'c'){
                while(editCondition != 'y' && editCondition != 'x'){
                  printf("Do you wish to exit editing this module? (y/n)");
                  if(editCondition == 'y'){

                  }
                  else if(editCondition == 'n'){
                    editCondition = 'x';
                  }
                  else printf("Invalid Command.");
                }
              }
            }
          locTwo = 0;
          }
        }
      } */
      break;

    case 'd':;
    case 'D':;
      printf("The function deleteModule is not yet implemented\n");
    /*  date deleteDate;
      int tempTime;
        printf("Choose a date from which you wish to delete a module: ");
        scanf("%d %d %d", &deleteDate.day, &deleteDate.month, &deleteDate.year);
        printf("These are the modules for the given date:\n");

        printf("Please enter the time for the Module that you wish to delete: ");
        scanf("%d", &tempTime);
        printf("Confirm? (y/n): ");
    */
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
