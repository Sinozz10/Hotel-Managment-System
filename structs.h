#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct
{
    char operator_Phone[50];
} phone;

typedef struct
{
    char roomnum[50];
    char roomtype[50];
    char roomstatus[50];
    float roomprice;
} rooms;

typedef struct
{
    long reservation_ID;
    rooms room;
    char name[200];
    char status[100];
    char guestnational_ID[50];
    char nights[30];
    char joined_date[50];
    char email[200];
    phone phone_number;
} reserver;

typedef struct 
{
    int day, month, year;
}date;

#endif