#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
// void readyState(int),
//      findCommand(char),
//      assignments(),
//      schedule(),
//      logOut();
//
// int login();


int main(void){
    login();
    if (loginID != 0){
        readyState();
    }
    return(0);
}
