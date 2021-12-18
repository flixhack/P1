#define MAX_LINE_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"


int main(void){
    login();
    if (loginID != 0){
        readyState();
    }
    return(0);
}
