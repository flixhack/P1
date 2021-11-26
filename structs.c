

struct date{
    int week,
        day,
        month,
        year;
    double hoursFree;
};
typedef date date;

struct module{
    date date;
    int startTime;   //Inten koder for starttidspunkt. 10:30 = 1030
    int duration;    //Antal minutter
    char *subject; 
};
typedef module module;

struct assignment{
    date startDate;
    date endDate;
    char *subject;
    int type;
};
typedef assignment assignment;