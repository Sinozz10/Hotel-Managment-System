#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "functions.h"


// 0-MAIN
int main()
{
    setConsoleColor(14);
    int operation;
    int counter = 0;
    printf("======== Welcome to the Hotel Management System ========\n");
    setConsoleColor(12);
    printf("Choose:\n1. login\n0. exit\n");
    setConsoleColor(15);
    do
    {
        if (scanf("%d", &operation) != 1)
        {
            setConsoleColor(14);
            printf("Invalid input, please try again\n");
            setConsoleColor(15);
            while (getchar() != '\n');
        }
        else if (operation == 0 || operation == 1)
        {
            break;
        }
        else
        {
            setConsoleColor(14);
            printf("Invalid input, please try again\n");
            setConsoleColor(15);
        }
    } while (1);
    if (operation == 0)
    {
        setConsoleColor(12);
        printf("Goodbye\n");
        setConsoleColor(15);
        exit(1);
    }
    char *pUsers = "users.txt";
    char Username[100], Password[100];
    printf("Login Menu\n");
    do
    {
        setConsoleColor(10);
        printf("Enter Username: ");
        scanf("%s", Username);
        printf("Enter Password: ");
        scanf("%s", Password);
        setConsoleColor(15);
    } while (!Check_userdata(Username, Password, pUsers, &counter));
    setConsoleColor(10);
    printf("Login successful\n");
    setConsoleColor(15);
    reserver reservation[500];
    char *pUsers1 = "Reservation.txt";
    char *pUsers2 = "rooms.txt";
    int count1, count2;
    char roomstatus[20];
    while (operation != 0)
    {
        setConsoleColor(2);
        printf("Choose an operation:\n1. Reserve a room\n2. Check-In\n3. Cancel Reservation\n4. Check-out\n5. Check Room Availability\n6. View Customer Details\n7. Edit Reservation Details\n8. Query (by search)\n9. Reservation Report\n0. Exit\n");
        scanf("%d", &operation);
        setConsoleColor(15);
        switch (operation)
        {
        case 0:
            setConsoleColor(12);
            printf("----------------------------------------\n");
            printf("Goodbye\n");
            setConsoleColor(15);
            exit(1);
        case 1:
            setConsoleColor(1);
            printf("Enter number of reservations: ");
            do{
                scanf("%d", &count1);
                if(isdigit(count1) || !(count1>0) )
                {
                    printf("Enter a valid number: ");
                }
            }while(!(count1>0));

            count2 = count1;
            loaddata(reservation, pUsers1, &count1);
            for (int i = 0; i < count2; i++)
            {
                if (reserveRoom(reservation, &count1, pUsers2, pUsers1) == 1)
                {
                    continue;
                }
                setConsoleColor(15);
                printf("----------------------------------------\n");
                printReservations(reservation,count1);
            }
            sortReservationsByDate(reservation, pUsers1, &count1);
            break;
        case 2:
            setConsoleColor(3);
            printf("===== Check-IN =====\n");
            checkIn(reservation, pUsers2, pUsers1);
            break;
        case 3:
            setConsoleColor(5);
            printf("===== Cancellation =====\n");
            cancellation(reservation, pUsers1, pUsers2);
            break;
        case 4:
            setConsoleColor(4);
            printf("===== Check-out =====\n");
            Checkout(reservation, pUsers1, pUsers2);
            break;
        case 5:
            setConsoleColor(6);
            printf("=== Check Availability ===\n");
            checkAvailability(pUsers2);
            break;
        case 6:
        {
            setConsoleColor(9);
            printf("===== View Customer Data =====\n");
            int num_inserted;
            int room_number;
            long resID;
            printf("Please enter your reservation ID or your room number \n");
            printf("Enter\n1.For Reservation ID\n2.For Room Number\n");
            do
            {
                scanf("%d", &num_inserted);
                if (!(num_inserted==1||num_inserted==2))
                {
                    printf("Invalid choice. Please enter 1 or 2.\n");
                }
            }while(!(num_inserted==1||num_inserted==2));
            switch(num_inserted)
            {
                case 1:
                printf("Enter Reservation ID: ");
                do
                {
                    scanf("%ld", &resID);
                    if (!(resID >= 100000 && resID <= 999999))
                    {
                        printf("Invalid ID. Please enter a valid ID.\n");
                    }
                } while (!(resID >= 100000 && resID <= 999999));
                viewCustomerDetails(pUsers1,resID);
                break;
                case 2:
                printf("Enter Room Number: ");
                do
                {
                    scanf("%d", &room_number);
                    if (!(room_number>=1000&&room_number<=4000))
                    {
                        printf("Invalid Room Number. Please enter a valid Room Number.\n");
                    }
                } while (!(room_number>=1000&&room_number<=4000));
                viewCustomerDetails(pUsers1,room_number);
            break;
            default:
            printf("Invalid choice.\n");
            break;
            }
        }
        break;
        case 7:
            edit_info(reservation, pUsers1, pUsers2);
            sortReservationsByDate(reservation, pUsers1, &count1);
            break;
        case 8:
            setConsoleColor(11); 
            printf("\n=== View All Reservations ===\n");
            printf("Choose search type:\n1. By customer name\n2. By room number\n3. By room status\n");
            do
            {
                scanf("%d", &operation);
                if (operation != 1 && operation != 2 && operation != 3)
                {
                    printf("Invalid choice. Please enter 1, 2 or 3.\n");
                }
            }while(operation != 1 && operation != 2 && operation != 3);
            switch (operation)
            {
            case 1:
                querybyname(pUsers1);
                break;
            case 2:
                printf("Enter room number: ");
                char roomnumber[20];
                do
                {
                    scanf("%s", roomnumber);
                    if (strlen(roomnumber) != 4)
                    {
                        printf("Invalid room number. Please enter a valid room number.\n");
                    }
                }while(strlen(roomnumber)!=4);
                querybyroomnumber(roomnumber, pUsers2, pUsers1);
                break;
            case 3:
                
                printf("Enter\n1. for Available rooms\n2. for Reserved rooms\n");
                scanf("%d", &operation);
                switch (operation)
                {
                case 1:
                    strcpy(roomstatus, "Available");
                    break;
                case 2:
                    strcpy(roomstatus, "Reserved");
                    break;
                default:
                    printf("Invalid choice, please re-enter 1 or 2\n");
                }
                querybyroomstatus(roomstatus, pUsers2);
                break;
            default:
                break;
            }
            break;
        case 9:
            setConsoleColor(13);
            printf("===== Reservation Report =====\n");
            print_report(reservation, pUsers1);
            break;
        default:
            setConsoleColor(15);
            printf("Invalid option, please try again.\n");
        }
        printf("Enter 1 to return to menu or enter 0 to exit\n");
        do
        {
            scanf("%d", &operation);
            if (operation != 1 && operation != 0)
            {
                printf("Invalid choice. Please enter 1. or 0.\n");
            }
        }while(operation != 1 && operation != 0);
        printf("------------------------------------------\n");
        setConsoleColor(15);
    }
    setConsoleColor(12);
    printf("Thank you :)\n");
    setConsoleColor(15);
    return 0;
}
