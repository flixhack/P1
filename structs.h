struct date{
    int week,
        day,
        month,
        year;
    double hoursFree;
};
typedef struct date date;

struct element{
    date date;
    int time;   //determines start- or end-time. 1930 = 19:30
    int duration;    //duration in minutes
    char *subject; 
    int type; //1: Module, 2: Assignment, 3: Homework, 4: Test
};
typedef struct element element;
