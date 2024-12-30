#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

void setConsoleColor(int color);
int casesensitve(char *str1, char *str2);
int Check_userdata(char *input_username, char *input_password, char *pUsers, int *counter);
void loaddata(reserver *reservation, char *pUsers1, int *count);
void clearInputBuffer();
int isValidDate(char *date);
int NumberOfNights(date checkin, date today);
void sortReservationsByDate(reserver *reservations, char *pusers1, int *count);
int reserveRoom(reserver *reservations, int *reservation_count, char *pUsers2, char *pUsers1);
void printReservations(reserver *reservations, int count);
void checkIn(reserver *reservation, char *pusers2, char *pusers1);
void cancellation(reserver *reservation, char *pusers1, char *pusers2);
void edit_info(reserver *reservations, char *pusers1, char *pusers2);
void checkAvailability(char *puser2);
void viewCustomerDetails(char *pusers1, int num_inserted);
void print_report(reserver *reservation, char *pusers1);
void querybyname(char *pusers1);
void querybyroomnumber(char *roomnumber, char *puser2, char *puser1);
void querybyroomstatus(char *roomstatus, char *puser2);
void Checkout(reserver *reservation, char *pusers1, char *pusers2);

#endif