#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
enum role {student = 1, teacher, administrator}; typedef enum role role;

void readyState(int),
     findCommand(char),
     assignments(),
     schedule(),
     logOut();

void calcWorkLoad();

int login();

int loggedIn = 0;

void printSchedule (int userID, int loginID){

}

void calcWorkLoad(){

}

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
     default:
      printf("Command not Found\n");  
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
  loggedIn = 0;

}
