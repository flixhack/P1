#include <stdio.h>
#include <stdlib.h>

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