#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
// #include "calendar.h"
// int loggedIn = 0; //needs to go

// void readyState(int),
//      findCommand(char),
//      assignments(),
//      schedule(),
//      logOut();
//
// int login();


int main(void){
    int loginVar = 0;
    loginVar = login();
    if (loginVar != 0){
        readyState(loginVar);
    }
    return(0);
}
