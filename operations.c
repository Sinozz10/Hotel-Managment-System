#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "structs.h"
#include "functions.h"

// 1.Login
int Check_userdata(char *input_username, char *input_password, char *pUsers, int *counter)
{
    FILE *user_file = fopen(pUsers, "r");
    if (user_file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char text[200], Username[100], Password[100];
    while (fgets(text, sizeof(text), user_file))
    {
        text[strcspn(text, "\n")] = '\0';
        if (sscanf(text, "%s %s", Username, Password) == 2)
        {
            if (strcmp(Username, input_username) == 0 && strcmp(Password, input_password) == 0)
            {
                fclose(user_file);
                return 1;
            }
        }
    }
    printf("Wrong username or password, please try again\n");
    (*counter)++;
    if (*counter == 5)
    {
        printf("Too many Failed Attempts,Try Again Later :(");
        fclose(user_file);
        exit(1);
    }
    fclose(user_file);
    return 0;
}

// Room Reservation
int reserveRoom(reserver *reservations, int *reservation_count, char *pUsers2, char *pUsers1)
{
    setConsoleColor(1);
    FILE *rooms_file = fopen(pUsers2, "r+");
    if (rooms_file == NULL)
    {
        printf("Error opening rooms file\n");
        exit(1);
    }
    reserver new_reservation;
    srand(time(NULL));
    long reservation_ID = 100000 + rand() % 900000;
    new_reservation.reservation_ID = reservation_ID;
    int flag=0;
    clearInputBuffer();

    printf("Enter Customer Name: ");
    while(!flag){
    fgets(new_reservation.name, sizeof(new_reservation.name), stdin);
    for (int i = 0; i<(strlen(new_reservation.name)-1); i++) {
        char c = new_reservation.name[i];
        if(new_reservation.name[0]==' ')
        {
            break;
        }
    if (!isalpha((unsigned char)c)&&c!=' ')
    {
        flag=0;
        break;
    }else flag=1;

    }if(!flag)printf("Enter a valid name: ");
    }

    flag=0;
    new_reservation.name[strcspn(new_reservation.name, "\n")] = '\0';

    printf("Enter Customer National ID: ");
    int valid;
    do {
        valid = 1;
        fgets(new_reservation.guestnational_ID,sizeof(new_reservation.guestnational_ID),stdin);
        new_reservation.guestnational_ID[strcspn(new_reservation.guestnational_ID, "\n")] = '\0';
        if (strlen(new_reservation.guestnational_ID) != 14) {
            valid = 0;
            printf("Invalid National ID. It must be exactly 14 characters long.\n");
        } 
        else 
        {
            for (int i = 0; i < 14; i++) {
                if (!isdigit(new_reservation.guestnational_ID[i])) {
                    valid = 0;
                    printf("Invalid National ID. It must contain only numbers.\n");
                    break;
                }
            }
        }
    }while (!valid);

    strcpy(new_reservation.status, "unconfirmed");
    flag=0;
    printf("Enter Email: ");

    while(!flag){
    fgets(new_reservation.email, sizeof(new_reservation.email), stdin);

    for (int i = 0; i<(strlen(new_reservation.email)-1); i++) {

    if (!strchr(new_reservation.email, '@') || !strchr(new_reservation.email, '.'))
    {
        flag=0;
        break;
    }else flag=1;

    }if(!flag)printf("Enter a valid Email: ");
    }

    flag=0;
    new_reservation.email[strcspn(new_reservation.email, "\n")] = '\0';

    printf("Enter Phone Number (area code): +2");

    while(!flag)
    {
    fgets(new_reservation.phone_number.operator_Phone, sizeof(new_reservation.phone_number.operator_Phone), stdin);

    for (int i = 0; i<(strlen(new_reservation.phone_number.operator_Phone)-1); i++) {
        char c = new_reservation.phone_number.operator_Phone[i];
    if (!isdigit((unsigned char)c)||strlen(new_reservation.phone_number.operator_Phone)-1!=11)
    {
        flag=0;
        break;
    }else flag=1;

    }if(!flag)printf("Enter a valid phone number (11 digits) : +2");
    }

    new_reservation.phone_number.operator_Phone[strcspn(new_reservation.phone_number.operator_Phone, "\n")] = '\0';

    printf("Enter Check-in Date (dd-mm-yyyy): ");
    do
    {
        fgets(new_reservation.joined_date, sizeof(new_reservation.joined_date), stdin);
        if(!isValidDate(new_reservation.joined_date))
        {
            printf("Invalid date. Please enter a date in the format (DD-MM-YYYY): ");
        }
    }while(!isValidDate(new_reservation.joined_date));

    new_reservation.joined_date[strcspn(new_reservation.joined_date, "\n")] = '\0';
    flag=0;
    printf("Enter Number of Nights: ");

    while(!flag){
        fgets(new_reservation.nights, sizeof(new_reservation.nights), stdin);

        for (int i = 0; i<(strlen(new_reservation.nights)-1); i++) {
            char m = new_reservation.nights[i];
        if (!isdigit((unsigned char)m))
        {
            flag=0;
            break;
        }else {flag=1;}

        }if(!flag)printf("Enter a valid number of nights: ");
    }
    flag=0;
    new_reservation.nights[strcspn(new_reservation.nights, "\n")] = '\0';

    printf("Select room category:\n");
    printf("1. SeaView\n");
    printf("2. LakeView\n");
    printf("3. GardenView\n");
    int category_choice;
    do
    {
        scanf("%d", &category_choice);
        if (category_choice == 1 || category_choice == 2 || category_choice == 3)
        {
            break;
        }
        printf("Invalid Input, Please Enter a valid choice\n");
    } while (1);
    switch(category_choice) 
    {
        case 1:
            strcpy(new_reservation.room.roomtype, "SeaView");
            break;
        case 2:
            strcpy(new_reservation.room.roomtype, "LakeView");
            break;
        case 3:
            strcpy(new_reservation.room.roomtype, "GardenView");
            break;
    }
    
    new_reservation.room.roomtype[strcspn(new_reservation.room.roomtype, "\n")] = '\0';
    int room_assigned = 0;
    char line[300], category[100], availability[20], price[20], room_number[10];
    long pos;
    while (fgets(line, sizeof(line), rooms_file))
    {
        pos = ftell(rooms_file) - strlen(line) - 1;
        sscanf(line, "%s %s %s %s", room_number, availability, category, price);
        if (strcmp(new_reservation.room.roomtype, category) == 0 && strcmp(availability, "Available") == 0)
        {
            snprintf(new_reservation.room.roomnum, sizeof(new_reservation.room.roomnum), "%d", room_number);
            printf("Do you want to save the reservation? (Y/N): ");
            char choice;
            do
            {
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y')
                {
                    break;
                }
                else if (choice == 'N' || choice == 'n')
                {
                    printf("Reservation cancelled\n");
                    return 1;
                }
                else
                {
                    printf("Invalid choice, please try again\n");
                }
            } while (1);
            room_assigned = 1;
            fseek(rooms_file, pos, SEEK_SET);
            fprintf(rooms_file, "%s Reserved %s %s ", room_number, category, price);
            break;
        }
    }
    fclose(rooms_file);
    if (!room_assigned)
    {
        printf("No available rooms in the requested category.\n");
        return 1;
    }
    FILE *reservation_file = fopen(pUsers1, "a");
    if (reservation_file == NULL)
    {
        printf("Error opening reservations file\n");
        exit(1);
    }
    strcpy(new_reservation.room.roomnum, room_number);
    fprintf(reservation_file, "%ld,%s,%s,%s,%s,%s,%s,%s,%s\n",
            new_reservation.reservation_ID,
            new_reservation.room.roomnum,
            new_reservation.status,
            new_reservation.name,
            new_reservation.guestnational_ID,
            new_reservation.nights,
            new_reservation.joined_date,
            new_reservation.email,
            new_reservation.phone_number.operator_Phone);
    fclose(reservation_file);
    reservations[*reservation_count] = new_reservation;
    (*reservation_count)++;
    printf("Reservation successful!\n");
    setConsoleColor(15);
    return 0;
}

// 4-CheckIn
void checkIn(reserver *reservation, char *pusers2, char *pusers1)
{
    long id;
    char date[15];
    printf("Enter Reservation ID: ");
    do
    {
    scanf("%ld", &id);
    if(!(id>=100000&&id<=999999))
    {
        printf("Invalid ID. Please enter a valid ID.\n");

    }
    }while(!(id>=100000&&id<=999999));

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(date, "%02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    
    FILE *file = fopen(pusers1, "r+");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[256];
    int i = 0;
    long pos;
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        pos = ftell(file) - strlen(line) - 1;
        sscanf(line, "%ld,%10[^,],%25[^,],%100[^,],%100[^,],%10[^,],%25[^,],%100[^,],%20[^\n]",
               &reservation[i].reservation_ID,
               reservation[i].room.roomnum,
               reservation[i].status,
               reservation[i].name,
               reservation[i].guestnational_ID,
               reservation[i].nights,
               reservation[i].joined_date,
               reservation[i].email,
               reservation[i].phone_number.operator_Phone);
        if (id == reservation[i].reservation_ID)
        {
            found = 1;
            if (strcmp(reservation[i].status, "confirmed") == 0)
            {
                printf("Already checked in\n");
                break;
            }
            if (strcmp(date, reservation[i].joined_date) != 0)
            {
                printf("Wrong date. Your reservation is for %s\n", reservation[i].joined_date);
                break;
            }
            printf("Do you want to save the Check-In? (Y/N): ");
            char choice;
            do
            {
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y')
                {
                    break;
                }
                else if (choice == 'N' || choice == 'n')
                {
                    printf("Check-In cancelled\n");
                    return;
                }
                else
                {
                    printf("Invalid choice, please try again\n");
                }
            } while (1);
            fseek(file, pos, SEEK_SET);
            strcpy(reservation[i].status, "confirmed");
            fprintf(file, "%ld,%s,%s,%s,%s,%s,%s,%s,%s  ", reservation[i].reservation_ID, reservation[i].room.roomnum, reservation[i].status, reservation[i].name, reservation[i].guestnational_ID, reservation[i].nights, reservation[i].joined_date, reservation[i].email, reservation[i].phone_number.operator_Phone);
            printf("Check-In successful\n");
            break;
        }
        i++;
    }
    if (!found)
    {
        printf("Reservation not found\n");
    }
    fclose(file);
}

// 5-Cancellation
void cancellation(reserver *reservation, char *pusers1, char *pusers2)
{
    int ID, room_number;
    printf("Enter your Reservation ID: \n");
    do
    {
    scanf("%d", &ID);
    if(!(ID>=100000&&ID<=999999))
    {
        printf("Invalid ID. Please enter a valid ID.\n");
    }
    } while (!(ID >= 100000 && ID <= 999999));

    printf("Enter your Room Number: \n");
    do
    {
        scanf("%d",&room_number);
        if (!(room_number >= 1000 && room_number <= 4000))
        {
            printf("Invalid Room Number. Please enter a valid Room Number.\n");
        }
    }while (!(room_number >= 1000 && room_number <= 4000));

    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL)
    {
        printf("Error opening Reservation.txt file.\n");
        exit(1);
    }
    char lines[500][500];
    int line_count = 0;
    int found = 0;
    char *pos;
    while (fgets(lines[line_count], sizeof(lines[line_count]), reservation_file))
    {
        int res_ID, room_num;
        sscanf(lines[line_count], "%d,%d", &res_ID, &room_num);
        pos = strstr(lines[line_count], ",confirmed");
        if (res_ID == ID && room_num == room_number)
        {
            if (pos == NULL)
                ;
            else if (*pos == ',')
            {
                printf("This room already checked in\n");
                return;
            }
            found = 1;
        }
        else
        {
            line_count++;
        }
    }
    fclose(reservation_file);
    
    if (!found)
    {
        printf("No reservation found for ID %d and room number %d.\n", ID, room_number);
        return;
    }
    printf("Are you sure you want to cancel the reservation? (Y/N): ");
    char choice;
    do
    {
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            printf("\"Reservation cancellation\" cancelled\n");
            return;
        }
        else
        {
            printf("Invalid choice, please try again\n");
        }
    } while (1);
    reservation_file = fopen(pusers1, "w");
    for (int i = 0; i < line_count; i++)
    {
        fprintf(reservation_file, "%s", lines[i]);
    }
    fclose(reservation_file);
    FILE *rooms_file = fopen(pusers2, "r");
    if (rooms_file == NULL)
    {
        printf("Error opening rooms.txt file.\n");
        exit(1);
    }
    char room_lines[500][300];
    int room_line_count = 0;
    while (fgets(room_lines[room_line_count], sizeof(room_lines[room_line_count]), rooms_file))
    {
        int room_num;
        sscanf(room_lines[room_line_count], "%d", &room_num);

        if (room_num == room_number)
        {
            char category[50];
            int price;
            sscanf(room_lines[room_line_count], "%d %*s %s %d", &room_num, category, &price);
            snprintf(room_lines[room_line_count], sizeof(room_lines[room_line_count]),
                     "%d Available %s %d\n", room_num, category, price);
        }
        room_line_count++;
    }
    fclose(rooms_file);
    rooms_file = fopen(pusers2, "w");
    for (int i = 0; i < room_line_count; i++)
    {
        fprintf(rooms_file, "%s", room_lines[i]);
    }
    fclose(rooms_file);
    printf("Reservation cancelled successfully.\n");
}

// 7-Checking Room Availability
void checkAvailability(char *puser2)
{
    FILE *fptr = fopen(puser2, "r");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[200][200];
    int line_count = 0;
    while (line_count < 200 && fgets(line[line_count], sizeof(line[line_count]), fptr) != NULL)
    {
        line[line_count][strcspn(line[line_count], "\n")] = '\0';
        line_count++;
    }
    fclose(fptr);
    printf("ALL rooms:\n");
    for (int i = 0; i < line_count; ++i)
    {
        char *token = strtok(line[i], " ");
        char *room_number = token;
        token = strtok(NULL, " ");
        char *availability = token;
        token = strtok(NULL, " ");
        char *room_category = token;
        token=strtok(NULL," ");
        char *price = token;
        printf("%s %s %s %s\n",room_number, availability, room_category, price);
    }
}

// 8-Viewing Customer Details
void viewCustomerDetails(char *pusers1, int num_inserted)
{
    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL)
    {
        printf("Error opening Reservation.txt file.\n");
        exit(1);
    }

    char line[500];
    int found = 0;

    while (fgets(line, sizeof(line), reservation_file))
    {
        int res_ID, room_num;
        sscanf(line, "%d,%d", &res_ID, &room_num);
        if (res_ID == num_inserted || room_num == num_inserted)
        {
            found = 1;
            break;
        }
    }
    fclose(reservation_file);

    if (!found)
    {
        printf("No reservation found \n");
        return;
    }
    else
    {
        char *tokens[100];
        char *token;
        int i = 0;
        token = strtok(line, ",");
        while (token != NULL)
        {
            tokens[i++] = token;
            token = strtok(NULL, ",");
        }
        printf("=======================================================\n");
        printf("Reservation ID: %s\n", tokens[0]);
        printf("Room Number: %s\n", tokens[1]);
        printf("Status: %s\n", tokens[2]);
        printf("Name: %s\n", tokens[3]);
        printf("National ID: %s\n", tokens[4]);
        printf("Nights: %s\n", tokens[5]);
        printf("Check-in Date: %s\n", tokens[6]);
        printf("Email: %s\n", tokens[7]);
        printf("Phone: %s\n", tokens[8]);
    }
}

// Printing Report
void print_report(reserver *reservation, char *pusers1)
{
    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL)
    {
        printf("Error opening Reservation.txt file.\n");
        exit(1);
    }
    char line[200], date[20];
    int i = 0;
    printf("Enter date: ");
    do
    {
        scanf("%s", date);
        if(!isValidDate(date))
        {
            printf("Invalid date. Please enter a valid date (DD-MM-YYYY): ");
        }
    } while (!isValidDate(date));

    while (fgets(line, sizeof(line), reservation_file))
    {
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%ld,%10[^,],%25[^,],%100[^,],%100[^,],%10[^,],%25[^,],%100[^,],%s",
               &reservation[i].reservation_ID,
               reservation[i].room.roomnum,
               reservation[i].status,
               reservation[i].name,
               reservation[i].guestnational_ID,
               reservation[i].nights,
               reservation[i].joined_date,
               reservation[i].email,
               reservation[i].phone_number.operator_Phone);
        if (strcmp(date, reservation[i].joined_date) == 0)
        {
            printf("=======================================================\n");
            printf("Reservation ID: %ld\n", reservation[i].reservation_ID);
            printf("Room Number: %s\n", reservation[i].room.roomnum);
            printf("Status: %s\n", reservation[i].status);
            printf("Name: %s\n", reservation[i].name);
            printf("National ID: %s\n", reservation[i].guestnational_ID);
            printf("Nights: %s\n", reservation[i].nights);
            printf("Check-in Date: %s\n", reservation[i].joined_date);
            printf("Email: %s\n", reservation[i].email);
            printf("Phone: %s\n", reservation[i].phone_number.operator_Phone);
            printf("=======================================================\n");
        }
        i++;
    }
    fclose(reservation_file);
}

// Query By name
void querybyname(char *pusers1) 
{
    char customer_name[200];
    printf("Enter customer name: ");
    while (getchar() != '\n'); 
    int valid = 0;
    while (!valid) {
        fgets(customer_name, sizeof(customer_name), stdin);
        customer_name[strcspn(customer_name, "\n")] = '\0'; 

        valid = 1;
        for (int i = 0; i < strlen(customer_name); i++) {
            char c = customer_name[i];
            if (!isalpha((unsigned char)c) && c != ' ') 
            {
                valid = 0;
                break;
            }
        }
        if (!valid) 
        {
            printf("Invalid input. Enter a valid name (letters and spaces only): ");
        }
    }
    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL) 
    {
        printf("Error: Unable to open file");
        exit(1);
    }
    char line[500];
    int found = 0;
    reserver temp_reservation;
    while (fgets(line, sizeof(line), reservation_file)) {
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%ld,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &temp_reservation.reservation_ID,
               temp_reservation.room.roomnum,
               temp_reservation.status,
               temp_reservation.name,
               temp_reservation.guestnational_ID,
               temp_reservation.nights,
               temp_reservation.joined_date,
               temp_reservation.email,
               temp_reservation.phone_number.operator_Phone);

        if (casesensitve(temp_reservation.name, customer_name) == 0) {
            found = 1;
            printf("\nReservation found:\n");
            printf("Reservation ID: %ld\n", temp_reservation.reservation_ID);
            printf("Room Number: %s\n", temp_reservation.room.roomnum);
            printf("Status: %s\n", temp_reservation.status);
            printf("Name: %s\n", temp_reservation.name);
            printf("National ID: %s\n", temp_reservation.guestnational_ID);
            printf("Nights: %s\n", temp_reservation.nights);
            printf("Check-in Date: %s\n", temp_reservation.joined_date);
            printf("Email: %s\n", temp_reservation.email);
            printf("Phone: %s\n", temp_reservation.phone_number.operator_Phone);
            printf("----------------------------------------\n");
        }
    }

    if (!found) {
        printf("No reservations found for customer: '%s'\n", customer_name);
    }

    fclose(reservation_file);
}

// Query By RoomNumber
void querybyroomnumber(char *roomnumber, char *puser2, char *puser1)
{
    FILE *fptr = fopen(puser2, "r");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[200][200];
    int line_count = 0;
    int room_found=0;
    while (line_count < 200 && fgets(line[line_count], sizeof(line[line_count]), fptr) != NULL)
    {
        line[line_count][strcspn(line[line_count], "\n")] = '\0';
        line_count++;
    }
    fclose(fptr);
    for (int i = 0; i < line_count; ++i)
    {
        char *token = strtok(line[i], " ");
        char *room_number = token;
        token = strtok(NULL, " ");
        char *availability = token;
        token = strtok(NULL, " ");
        char *room_category = token;
        token = strtok(NULL, " ");
        char *price = token;
        if (strcmp(room_number, roomnumber) == 0)
        {
            room_found=1;
            if (strcmp(availability, "Available") == 0)
            {
                printf("Room is available and has no guest\n");
            }
            else if (strcmp(availability, "Reserved") == 0)
            {
                int room = atoi(room_number);
                viewCustomerDetails(puser1, room);
            }
        }
    }
    if(!room_found)
    {
        printf("Room number not found\n");
    }
}

// Query By RoomStatus
void querybyroomstatus(char *roomstatus, char *puser2)
{
    FILE *fptr = fopen(puser2, "r");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[200][200];
    int line_count = 0;
    while (line_count < 200 && fgets(line[line_count], sizeof(line[line_count]), fptr) != NULL)
    {
        line[line_count][strcspn(line[line_count], "\n")] = '\0';
        line_count++;
    }
    fclose(fptr);
    printf("%s rooms:\n", roomstatus);
    for (int i = 0; i < line_count; ++i)
    {
        char *token = strtok(line[i], " ");
        char *room_number = token;
        token = strtok(NULL, " ");
        char *availability = token;
        token = strtok(NULL, " ");
        char *room_category = token;
        token = strtok(NULL, " ");
        char *price = token;
        if (strcmp(availability, roomstatus) == 0)
        {
            printf("%s %s %s %s\n", room_number, availability, room_category, price);
        }
    }
}

void Checkout(reserver *reservation, char *pusers1, char *pusers2){
    int roomnum;
    int number_of_nights;
    date today, checkindate;
    printf("Enter room number: ");
    do {
        scanf("%d", &roomnum);
        if (!(roomnum >= 1000 && roomnum <= 4000)) {
            printf("Invalid Room Number. Please enter a valid Room Number (1000-4000): ");
        }
    } while (!(roomnum >= 1000 && roomnum <= 4000));
    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    FILE *rooms_file = fopen(pusers2, "r");
    if (rooms_file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char line[500], room_category[20], name[20];
    int found = 0;
    float room_price = 0;
    while (fgets(line, sizeof(line), rooms_file)) {
        int curr_room;
        char status[20];
        char category[50];
        float price;

        sscanf(line, "%d %s %s %f", &curr_room, status, category, &price);
        if (curr_room == roomnum) {
            found = 1;
            room_price = price;
            strcpy(room_category, category);
            if (strcmp(status, "Available") == 0) {
                printf("This room is already available\n");
                fclose(rooms_file);
                return;
            }
            break;
        }
    }
    fclose(rooms_file);
    if (!found) {
        printf("Room not found\n");
        return;
    }
    char lines[500][500], current[500];
    int line_count = 0, reservation_found = 0;
    reserver curr_reservation;
    char room_number[10], status[20], check_in_date[20];
    int nights;
    while (fgets(current, sizeof(current), reservation_file)) {
        strcpy(lines[line_count], current);
        current[strcspn(current, "\n")] = '\0';
        
        
        sscanf(current, "%ld,%[^,],%[^,],%[^,],%[^,],%d,%[^,]",
            &curr_reservation.reservation_ID,
            room_number,
            status,
            curr_reservation.name,
            curr_reservation.guestnational_ID,
            &nights,
            check_in_date);

        if (atoi(room_number) == roomnum) {
            reservation_found = 1;
            strcpy(name, curr_reservation.name);
            sscanf(check_in_date, "%d-%d-%d", &checkindate.day, &checkindate.month, &checkindate.year);
            if (strcmp(status, "unconfirmed") == 0) {
                printf("The reservation is not confirmed yet\n");
                fclose(reservation_file);
                return;
            }
        } else {
            line_count++;
        }
    }
    fclose(reservation_file);

    if (!reservation_found) {
        printf("No reservation found for this room\n");
        return;
    }
    char todaydate[20];
    printf("Enter today's date: ");
    do
    {
        scanf("%s", todaydate);
        if(!isValidDate(todaydate))
        {
            printf("Invalid date. Please enter a valid date (DD-MM-YYYY): ");
        }
    } while (!isValidDate(todaydate));
    sscanf(todaydate, "%d-%d-%d",  &today.day, &today.month, &today.year);
    number_of_nights = NumberOfNights(checkindate, today);
    if (number_of_nights < 0)
    {
        printf("You cannot check out before the check in date\n");
        return;
    }
    else if (number_of_nights == 0) number_of_nights = 1;
    
    printf("Are you sure you want to Check-out? (Y/N): ");
    char choice;
    do
    {
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            printf("Check-out cancelled\n");
            return;
        }
        else
        {
            printf("Invalid choice, please try again\n");
        }
    } while (1);

    printf("\n=== Check-out Bill ===\n");
    printf("Room Number: %d\n", roomnum);
    printf("Room Category: %s\n", room_category);
    printf("Guest Name: %s\n", name);
    printf("Number of nights: %d\n", number_of_nights);
    printf("Rate per Night: $%.1f\n", room_price);
    printf("Total Amount: $%.1f\n", room_price*number_of_nights);
    printf("==================\n");

    reservation_file = fopen(pusers1, "w");
    if (reservation_file == NULL) {
        printf("Error updating reservation file\n");
        exit(1);
    }
    
    for (int i = 0; i < line_count; i++) {
        fputs(lines[i], reservation_file);
    }
    fclose(reservation_file);

    // Update room status to Available
    rooms_file = fopen(pusers2, "r");
    if (rooms_file == NULL) {
        printf("Error opening rooms file\n");
        exit(1);
    }

    char room_lines[500][300];
    int room_line_count = 0;
    while (fgets(room_lines[room_line_count], sizeof(room_lines[room_line_count]), rooms_file)) {
        room_line_count++;
    }
    fclose(rooms_file);

    rooms_file = fopen(pusers2, "w");
    if (rooms_file == NULL) {
        printf("Error updating rooms file\n");
        return;
    }
    for (int i = 0; i < room_line_count; i++) {
        int curr_room;
        char status[20], category[50];
        float price;
        sscanf(room_lines[i], "%d %s %s %f", &curr_room, status, category, &price);
        
        if (curr_room == roomnum) {
            fprintf(rooms_file, "%d Available %s %.0f\n", curr_room, category, price);
        } else {
            fputs(room_lines[i], rooms_file);
        }
    }
    fclose(rooms_file);
    printf("Check-out successful!\n");
}
