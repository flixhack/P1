#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  int loginlength = 13;
  char loginAndPwFromDB[20];
  // char userName[loginlength];
  // char pw[loginlength];
  char loginAndPwToTest[13];

  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  printf("\nIndtast login og password: ");
  scanf("%10[0-9a-zA-Z ]", &loginAndPwToTest );
  // scanf("\n%s", &pw );



  for (int i = 0; i < loginlength; i++) {
    printf("%c\n", loginAndPwToTest[i] );
  }

  FILE *in_file = fopen("users.txt", "r");
  if (in_file == NULL) {
          printf("Error file missing\n");
          exit(-1);
  }


  while ((read = getline(&line, &len, in_file)) != -1) {
    // printf("Retrieved line of length %zu:\n", read);
    printf("%s", line);
}

  // while ( fscanf(in_file,"%s", loginAndPwFromDB) == 1) {
  //         //Add a for loop till strstr(string, student) does-not returns null.
  //     for (int i = 0; i < 21; i++) {
  //       printf("%c\n", loginAndPwFromDB[i] );
  //     }
  //   if(strstr(loginAndPwToTest, loginAndPwFromDB) != 0) {//if match found
  //     printf("\n%sUser Found");
  //     }
  //
  //   }
  fclose(in_file);


  return 0;
}
