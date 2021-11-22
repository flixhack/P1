#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void accessCalendar (){
    int c;
    FILE *file;
    file = fopen("calendar.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}

//shamelessly stolen from https://stackoverflow.com/questions/29429384/search-string-in-a-file-in-c

void accessDate (){
        int num =0;
        char word[2000];
        char string[50];
        char calendar[100] = {0};

        while(calendar[0]!= '0')
        {
                FILE *in_file = fopen("calendar.txt", "r");
                if (in_file == NULL)
                {
                        printf("Error file missing\n");
                        exit(-1);
                }

                printf("please enter a word(enter 0 to end)\n");
                scanf("%s", calendar);
                while ( fscanf(in_file,"%s", string) == 1)
                {
                        //Add a for loop till strstr(string, student) does-not returns null. 
                        if(strstr(string, calendar)!=0) {//if match found
                                num++;
                        }
                }
                printf("we found the word %s in the file %d times\n", calendar ,num );
                num = 0;
                fclose(in_file);
        }
        return 0;
}