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

// char printTime(int){
    
// }  //modtag en stored int og print den som tekst. eks: int == 945 bliver til 9:45

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
