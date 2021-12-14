#include "dbManager.h"
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

void printSchedule (int userID, int loginID){

}

double calcWorkLoad(element element){
    double result = 0;
    int days = 0;
    switch (element.type){
        case 1: //Module
            result = element.duration / 60;
            break;
        case 2: //Assignment
            
            break;
        case 3: //Homework

            break;
        case 4: //Test

            break;
        default:
            break;
    }
    printf("Calculated workload: %lf\n", result); //TESTING PURPOSES. REMEMBER TO REMOVE!
    return result;
}

int readTime(char input[]){
    int n1 = 0;
    if (input[1] == ':'){
      n1 = ((input[0] - '0') * 100) + ((input[2] - '0') * 10) + (input[3] - '0');
    }
    else {
      n1 = ((input[0] - '0') * 1000) + ((input[1] - '0')*100) + ((input[3] - '0') * 10) + (input[4] - '0');
    }
    return n1;
}

int promptTime(void){
    char input[5];
    scanf("%s", input);
    int time = readTime(input);
    return time;
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

  int loginID = login();
  readyState(loginID);  
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
  char mode;
  char database[MAX_LINE_LENGTH] = "calendar.txt";
  char tempTime[MAX_LINE_LENGTH];
  char newLine[MAX_LINE_LENGTH];
  int run = 1, locOne = 0, locTwo = 0, lineLoc = 0;
  char command;
  while (run == 1){
    printf("Create a module, Edit a module, delete a module or go back? (C/E/D/B): ");
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
        printf("Insert a year, month and a day for the module to take place: ");
        scanf("%d %d %d", &newDate.day, &newDate.month, &newDate.year);
        sprintf(tempTime, "%d/%d/%d", newDate.day, newDate.month, newDate.year);

        findSection(tempTime, database, &locOne, &locTwo);

        if (&locTwo == -1){
          callDatabase(mode, database, , tempTime)
          tempTime = 
          callDatabase(mode, database, )
        }

        
        printf("Insert the starting time, duration and module: ");

        scanf("%d %d %s", &newModule.time, &newModule.duration, newModule.subject);
        
        printf("Is this module correct? (y/n)\n\n");
        printf("Module: %s Date: %d/%d/%d   Duration: %d   Time: %d\n", newModule.subject, newDate.day, newDate.month, newDate.year, newModule.duration, newModule.time);
        
        sprintf(newLine, "%s_%d_%d_%s", newModule.time, newModule.duration, newModule.type, newModule.subject);
        callDatabase(mode, database, locOne + 1, newLine);
        break;
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
      
      callDatabase(mode, database, lineLoc);

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

    printf("Enter Line: (Format: HH:MM_DURATION_1_SUBJECT)");
    scanf(" %s", newLine);

    databaseEdit(&mode, &lineNum, newLine, database);

}

void logOut(){
  loggedIn = 0;

}
