typedef enum types {mod = 1, ass, hmw, tst}; types;

typedef struct date{
    int week,
        day,
        month,
        year;
    double hoursFree;
} date;

typedef struct element{
    date startDate;
    date endDate;
    char time[100];   //determines start- or end-time. 
    int duration;    //duration in minutes
    char subject[100]; 
    int type; //1: Module, 2: Assignment, 3: Homework, 4: Test
} element;
