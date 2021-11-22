#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"

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
    int loggedIn = 0;

    printf("\nEnter your username (T, S, A): ");
    scanf("%c", &loginScan);
    switch (loginScan){
        
    case 'S':
        loggedIn = 1;
        break;
    case 'T':
        loggedIn = 2;
        break;
    case 'A':
        loggedIn = 3;
        break;
    default:
        break;
    }
    return(loggedIn);
}

void readyState(int loginVar){
    char command;

    while (loginVar != 0) {
        scanf(" %c", &command);
        findCommand(command);

    }
}

void findCommand(char command){
    switch (command){

    case 'A':
        assignments();
        break;
    case 'S':
        schedule();
        break;
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
    
}