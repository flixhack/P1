#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "calendar.h"
int loggedIn = 0;

void readyState(int),
     findCommand(char),
     assignments(),
     schedule(),
     logOut();

int login();


int main(void){
    int loginVar = 0;
    loginVar = login();
    if (loginVar != 0){
        readyState(loginVar);
    }
    return(0);
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

void assignments(){

}

void schedule(){

}

void logOut(){
  loggedIn = 0;

}
