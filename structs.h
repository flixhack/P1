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
    char *time;   //determines start- or end-time. 
    int duration;    //duration in minutes
    char *subject; 
    int type; //1: Module, 2: Assignment, 3: Homework, 4: Test
} element;
