

struct date{
    int week,
        day,
        month,
        year;
    double hoursFree;
};
typedef date date;

struct element{
    date date;
    int time;   //determines start- or end-time. 1930 = 19:30
    int duration;    //Antal minutter
    char *subject; 
    int type; //1: Module, 2: Assignment, 3: Homework, 4: Test
};
typedef element element;
