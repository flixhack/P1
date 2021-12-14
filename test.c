#include <stdio.h>
#include <stdlib.h>
#include "dbManager.h"

date stringToDateConvert(char);
void readSection(int locOne, int locTwo, char tempDB[][100], char databaseSelect[]);


int main() {
  char databaseSelect[12] = "calendar.txt";
  char buffer[MAX_LINE_LENGTH];
  char str[999];
  int count = 0;
  int currentDate;
  int lastestDate = 0;

  FILE *readFile = fopen(databaseSelect, "r");
  FILE *writeTemp = fopen("replace.tmp", "w");

  if (readFile == NULL) {
    printf("Database file not found. Contact an administrator.");
    exit(EXIT_FAILURE);

    readSection(&locOne, &locTwo, char tempDB[][100], char databaseSelect[]);



  }


  void readSection(int locOne, int locTwo, char tempDB[][100], char databaseSelect[]) {
      //If statement uses the location variables assigned earlier (locOne and locTwo) to only store the necesarry text
      int lineCount = countLines(char *calendar.txt);
      int bytes = 0;
      char string[MAX_LINE_LENGTH];

      FILE *readFile = fopen(databaseSelect, "r");
      if (readFile == NULL){
          printf("Database file not found. Contact an administrator\n");
          exit(EXIT_FAILURE);
      }

      bytes = locOne;
      int i = 0;
      while (fscanf(readFile, "%s", string) == 1) {
          if (lineCount > bytes && lineCount < locTwo) {
              strcpy(tempDB[i], string);
              i++;
              bytes++;
              // if (string[strlen(string) - 1] != '\n') {
              //     printf("\n");
              // }
          }
          lineCount++;
          printf("string");
      }
      fclose(readFile);
  }

  stringToDateConvert(char string[], char separator);
  currentDate = date;

  while(fscanf(databaseSelect, "%s", str) != EOF && *currentDate != lastestDate){

    //if(*currentDate > lastestDate) {



    return lastestDate;
    //}


  }



  return 0;
}

date stringToDateConvert(char string[], char separator){
    date date;
        int parseSwitch = 1, k;
    int k;
    char day[2];
    char month[2];
    char year[4];
    int dayNumCount = 0;
    int monthNumCount = 0;
    int yearNumCount = 0;
    // char separator;
    for (k = 0; k < 10; k++) {
        if (string[k] == 'separator') {
            parseSwitch++;
        }
        else if (string[k] != 'separator' && parseSwitch == 1) {
            day[dayNumCount] = string[k];
            dayNumCount++;
        }
        else if (string[k] != 'separator' && parseSwitch == 2) {
            month[monthNumCount] = string[k];
            monthNumCount++;
        }
        else if (string[k] != 'separator' && parseSwitch == 3) {
            year[yearNumCount] = string[k];
            yearNumCount++;
        }
    }
    date.day = atoi(day);
    date.month = atoi(month);
    date.year = atoi(year);


    return date;
}
