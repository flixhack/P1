#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbManager.h"

void lineSplit(char [][100], int *, char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH], char [][MAX_LINE_LENGTH]);


int lineLoc = 0;
char testInput[MAX_LINE_LENGTH];


int main() {
  char password[20];
  char string[100];
  char databaseSelect[100] = "users.txt";
  char search[100] = "USERS";
  char tempDB[100][100];
  char userID[100][MAX_LINE_LENGTH];
  char usernameAndPassword[100][MAX_LINE_LENGTH];
  char loginID[100][MAX_LINE_LENGTH];


  printf("\nIndtast username: ");
  scanf("%s", &testInput);
  printf("\nIndtast password: ");
  scanf("%s", &password);

  strcat(testInput, "_");
  strcat(testInput, password);

  printf("\n%s", testInput);

  

  findSection(search, databaseSelect, &locOne, &locTwo);

  readSection(locOne, locTwo, tempDB, databaseSelect);
  // for (int i = 0; i < 10; i++) {
  //   printf("%s, i er = %i", tempDB[i], i);
  // }
  for (int i = locOne; i <= locTwo; i++) {
    // printf("\nFUCK IAN");
    lineSplit(tempDB, &i, userID, usernameAndPassword, loginID);
    printf("\n[%i] - %s", i, tempDB[i]);
    printf("\n%i, uid = %s, uname = %s, loginID = %s", i, userID[i], usernameAndPassword[i], loginID[i]);

  }

  // findLine(string, &lineLoc, testInput, &locOne, databaseSelect);
  printf("%i", lineLoc);






  return 0;
}

void lineSplit (char tempDB[][100], int *lineLoc, char userID[][MAX_LINE_LENGTH], char usernameAndPassword[][MAX_LINE_LENGTH], char loginID[][MAX_LINE_LENGTH]) {
    int parseSwitch = 1, k;
    //printf("\nlineSplit: [%i] %s", *lineLoc, tempDB[*lineLoc]);

    for (k = 0; k < MAX_LINE_LENGTH; k++) {
        if (tempDB[*lineLoc][k] == ';') {
            parseSwitch++;
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 1) {
            userID[*lineLoc][k] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 2) {
            usernameAndPassword[*lineLoc][k - countChars(tempDB[*lineLoc], 1, ';')] = tempDB[*lineLoc][k];
        }
        else if (tempDB[*lineLoc][k] != ';' && parseSwitch == 3) {
            loginID[*lineLoc][k - countChars(tempDB[*lineLoc], 2, ';')] = tempDB[*lineLoc][k];
        }
    }
}
