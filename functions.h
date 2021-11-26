#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void readyState(int),
     findCommand(char),
     assignments(),
     schedule(),
     logOut();

int login();

int loggedIn = 0;

void printSchedule (int userID, int loginID){

}

int readTime(void){
    int n1 = 0;
    int n2 = 2;
    char col;
    scanf(" %i", &n1);
    scanf("%c", &col);
    if (col != ":"){
        return 0;
    }
    else {
        scanf("%i", &n2);
    }
    if (n1 > 24 || n1 < 0){
        return 0;
    }
    if (n2 > 60 || n2 < 0){
        return 0;
    }
    // God fucking help me
    /* if (n2 < 10 && (n2 != 09 || n2 != 08 || n2 != 07 || n2 != 06 || n2 != 05 || n2 != 04 || n2 != 03 || n2 != 02 || n2 != 01 || n2 != 00){
        return 0;
    } */
    
}

const char * recieveString(){
    int i = 0;



    char string[] = (char*)malloc(i * sizeof(char));
    free(string[]);

    while (scanf(" %c",&string[i])){
        i++;
    }


    return string[];
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
  loggedIn = 0;

}
