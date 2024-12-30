#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include "structs.h"
#include "functions.h"
void setConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
#include <unistd.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
void setConsoleColor(const char *color)
{
    printf("%s", color);
}
#endif

// Load Data from File
void loaddata(reserver *reservation, char *pUsers1, int *count)
{
    FILE *file = fopen(pUsers1, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int i = 0;
    char data[500];
    while (fgets(data, sizeof(data), file))
    {
        data[strcspn(data, "\n")] = '\0';
        sscanf(data, "%ld,%49s,%199s,%99s,%49s,%29s,%49s,%199s,%49s\n",
               &reservation[i].reservation_ID,
               reservation[i].room.roomnum,
               reservation[i].status,
               reservation[i].name,
               reservation[i].guestnational_ID,
               reservation[i].nights,
               reservation[i].joined_date,
               reservation[i].email,
               reservation[i].phone_number.operator_Phone);
        i++;
    }
    *count = i;
    fclose(file);
}


int NumberOfNights(date checkin, date today) {
    struct tm tm_date1 = {0};
    struct tm tm_date2 = {0};
    time_t time1, time2;

    tm_date1.tm_mday = checkin.day;
    tm_date1.tm_mon = checkin.month - 1;
    tm_date1.tm_year = checkin.year - 1900;

    tm_date2.tm_mday = today.day;
    tm_date2.tm_mon = today.month - 1;
    tm_date2.tm_year = today.year - 1900;

    time1 = mktime(&tm_date1);
    time2 = mktime(&tm_date2);

    double difference = difftime(time2, time1) / (60 * 60 * 24);
    return (int)difference;
}

// Printing Reservations
void printReservations(reserver *reservations, int count)
{
    int i = count - 1;
    setConsoleColor(12);
    printf("Reservation ID: %ld\n", reservations[i].reservation_ID);
    printf("Room Number: %s\n", reservations[i].room.roomnum);
    printf("Room Type: %s\n", reservations[i].room.roomtype);
    printf("Status: %s\n", reservations[i].status);
    printf("Name: %s\n", reservations[i].name);
    printf("National ID: %s\n", reservations[i].guestnational_ID);
    printf("Nights: %s\n", reservations[i].nights);
    printf("Check-in Date: %s\n", reservations[i].joined_date);
    printf("Email: %s\n", reservations[i].email);
    printf("Phone: %s\n", reservations[i].phone_number.operator_Phone);
    printf("-----------------------------------\n");
    setConsoleColor(15);
}

//Bonus-Sorting by Date
void sortReservationsByDate(reserver *reservations, char *pusers1, int *count) 
{
    FILE *file = fopen(pusers1, "r");
    if (file == NULL) {
        printf("Error opening file for sorting\n");
        exit(1);
    }
    reserver temp_reservations[500];
    int reservationCount = 0;
    char line[500];
    while (fgets(line, sizeof(line), file) && reservationCount < 500) {
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &temp_reservations[reservationCount].reservation_ID,
               temp_reservations[reservationCount].room.roomnum,
               temp_reservations[reservationCount].status,
               temp_reservations[reservationCount].name,
               temp_reservations[reservationCount].guestnational_ID,
               temp_reservations[reservationCount].nights,
               temp_reservations[reservationCount].joined_date,
               temp_reservations[reservationCount].email,
               temp_reservations[reservationCount].phone_number.operator_Phone);
        reservationCount++;
    }
    fclose(file);
    // Bubble sort
    for (int i = 0; i < reservationCount - 1; i++) {
        for (int j = 0; j < reservationCount - i - 1; j++) {
            int day1, month1, year1, day2, month2, year2;
            sscanf(temp_reservations[j].joined_date, "%d-%d-%d", &day1, &month1, &year1);
            sscanf(temp_reservations[j + 1].joined_date, "%d-%d-%d", &day2, &month2, &year2);
            
            int date1_val = year1 * 10000 + month1 * 100 + day1;
            int date2_val = year2 * 10000 + month2 * 100 + day2;
            
            if (date1_val > date2_val) {
                // Swap reservations
                reserver temp = temp_reservations[j];
                temp_reservations[j] = temp_reservations[j + 1];
                temp_reservations[j + 1] = temp;
            }
        }
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temp file\n");
        exit(1);
    }
    for (int i = 0; i < reservationCount; i++) {
        fprintf(tempFile, "%ld,%s,%s,%s,%s,%s,%s,%s,%s\n",
                temp_reservations[i].reservation_ID,
                temp_reservations[i].room.roomnum,
                temp_reservations[i].status,
                temp_reservations[i].name,
                temp_reservations[i].guestnational_ID,
                temp_reservations[i].nights,
                temp_reservations[i].joined_date,
                temp_reservations[i].email,
                temp_reservations[i].phone_number.operator_Phone);
    }
    fclose(tempFile);
    remove(pusers1);
    rename("temp.txt", pusers1);
    for (int i = 0; i < reservationCount; i++) {
        reservations[i] = temp_reservations[i];
    }
    *count = reservationCount;
}
