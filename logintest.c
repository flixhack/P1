#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbManager.h"

int lineLoc = 0;
char testInput[MAX_LINE_LENGTH];


int main() {
  char password[20];
  char string[100];
  char databaseSelect[100] = "users.txt";
  char search[100] = "USERS";
  char tempDB[100][100];

  printf("\nIndtast username: ");
  scanf("%s", &testInput);
  printf("\nIndtast password: ");
  scanf("%s", &password);

  strcat(testInput, "_");
  strcat(testInput, password);

  printf("\n%s", testInput);



  findSection(string, &locOne, &locTwo, search, databaseSelect);

  readSection(string, &locOne, &locTwo, tempDB, databaseSelect);
  // for (int i = 0; i < 10; i++) {
  //   printf("%s, i er = %i", tempDB[i], i);
  // }

  findLine(string, &lineLoc, testInput, &locOne, databaseSelect);
  printf("%i", lineLoc);






  return 0;
}
