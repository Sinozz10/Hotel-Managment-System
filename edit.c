#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "structs.h"
#include "functions.h"

// 6-Editing Reservations
void edit_info(reserver *reservations, char *pusers1, char *pusers2){
    setConsoleColor(9);
    long num_inserted;
    printf("Enter your reservation ID or room number:\n");
    if (scanf("%ld", &num_inserted) != 1)
    {
        printf("Invalid input\n");
        return;
    }

    FILE *reservation_file = fopen(pusers1, "r");
    if (reservation_file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    char lines[500][500];
    int line_count = 0;
    int matched_line = -1;  // Add this to store which line matched
    char line_matched[1000] = "";

    // Modified reading loop
    while (fgets(lines[line_count], sizeof(lines[line_count]), reservation_file))
    {
        int res_ID, room_num;
        if (sscanf(lines[line_count], "%d,%d", &res_ID, &room_num) != 2)
        {
            line_count++;
            continue;
        }

        if (res_ID == num_inserted || room_num == num_inserted)
        {
            strcpy(line_matched, lines[line_count]);
            matched_line = line_count;  // Store the matched line index
        }
        line_count++;  // Keep counting lines
    }
    fclose(reservation_file);

    if (strlen(line_matched) == 0)
    {
        printf("Reservation not found\n");
        return;
    }

    printf("\nCurrent reservation details:\n%s", line_matched);

    // Count the number of tokens first
    char temp_line[1000];
    strcpy(temp_line, line_matched);
    char *temp_token = strtok(temp_line, ",");
    int token_count = 0;
    while (temp_token != NULL)
    {
        token_count++;
        temp_token = strtok(NULL, ",");
    }

    // Dynamically allocate memory for hold
    char **hold = (char **)malloc(token_count * sizeof(char *));
    if (hold == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < token_count; i++)
    {
        hold[i] = (char *)malloc(100 * sizeof(char));
        if (hold[i] == NULL)
        {
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
            {
                free(hold[j]);
            }
            free(hold);
            printf("Memory allocation failed\n");
            return;
        }
    }

    // Tokenize again for actual processing
    char *token = strtok(line_matched, ",");
    int counter_tokenising = 0;
    while (token != NULL && counter_tokenising < token_count)
    {
        strncpy(hold[counter_tokenising], token, 99);
        hold[counter_tokenising][99] = '\0';
        counter_tokenising++;
        token = strtok(NULL, ",");
    }

    if (strstr(hold[3], "confirmed"))
    {
        // Free allocated memory before returning
        for (int i = 0; i < token_count; i++)
        {
            free(hold[i]);
        }
        free(hold);
        printf("Cannot edit confirmed reservation\n");
        return;
    }

    printf("\nEdit options:\n1. Name\n2. Email\n3. Check-in date\n4. Room category\n5. Number of nights\n6. Phone Number\n");
    int number_choice;
    if (scanf("%d", &number_choice) != 1 || number_choice < 1 || number_choice > 6)
    {
        // Free allocated memory before returning
        for (int i = 0; i < token_count; i++)
        {
            free(hold[i]);
        }
        free(hold);
        printf("Invalid choice\n");
        return;
    }
    getchar();
    char new_value[100];

    
    char choice;
    switch (number_choice)
    {
    case 1:
        printf("Enter new name:\n");
        fgets(new_value, sizeof(new_value), stdin);
        new_value[strcspn(new_value, "\n")] = '\0';
        if (strlen(new_value) < 2)
        {
            printf("Name too short\n");
            break;
        }
        printf("Are you sure you want to change your name? (Y/N): ");
        do
        {
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                break;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Edit cancelled\n");
                return;
            }
            else
            {
                printf("Invalid choice, please try again\n");
            }
        } while (1);
        strncpy(hold[3], new_value, 99);
        hold[3][99] = '\0';
        break;
    case 2:
        printf("Enter new email:\n");
        do
        {
            fgets(new_value, sizeof(new_value), stdin);
            new_value[strcspn(new_value, "\n")] = '\0';
            if (!strchr(new_value, '@') || !strchr(new_value, '.'))
            {
                printf("Invalid email format\n");
            }
        } while (!strchr(new_value, '@') || !strchr(new_value, '.'));
        
        printf("Are you sure you want to change your email? (Y/N): ");
        do
        {
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                break;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Edit cancelled\n");
                return;
            }
            else
            {
                printf("Invalid choice, please try again\n");
            }
        } while (1);
        strncpy(hold[7], new_value, 99);
        hold[7][99] = '\0';
        break;
    case 3:
        printf("Enter new date (DD-MM-YYYY):\n");
        do
        {
            fgets(new_value, sizeof(new_value), stdin);
            new_value[strcspn(new_value, "\n")] = '\0';
            if (!isValidDate(new_value))
            {
                printf("Invalid date, please re-enter the date\n");
            }
        } while (!isValidDate(new_value));
        char newdate[20];
        time_t now = time(NULL);
        struct tm *t = localtime (&now);
        sprintf(newdate, "%d-%d-%d", t->tm_mday, t->tm_mon+1, t->tm_year+1900);
        if (strcmp(new_value, newdate) == -1)
        {
            printf("You can't change the check-in date\n");
            return;
        }
        printf("Are you sure you want to edit the check-in date? (Y/N): ");
        do
        {
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                break;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Edit cancelled\n");
                return;
            }
            else
            {
                printf("Invalid choice, please try again\n");
            }
        } while (1);
        strncpy(hold[6], new_value, 99);
        hold[6][99] = '\0';
        break;
    case 4:
        printf("Select room category:\n");
        printf("1. SeaView\n");
        printf("2. LakeView\n");
        printf("3. GardenView\n");
        int category_choice;
        do
        {
            scanf(" %d", &category_choice);
            if (category_choice == 1 || category_choice == 2 || category_choice == 3)
            {
                break;
            }
            printf("Invalid Input, Please Enter a valid choice\n");
        } while (1);
        char selected_category[20] = "";
        switch(category_choice) 
        {
            case 1:
                strcpy(selected_category, "SeaView");
                break;
            case 2:
                strcpy(selected_category, "LakeView");
                break;
            case 3:
                strcpy(selected_category, "GardenView");
                break;
            default:
                printf("Invalid choice, please re-enter 1 or 2 or 3\n");
        }
        char old_room_number[100];
        strncpy(old_room_number, hold[1], sizeof(old_room_number) - 1);
        old_room_number[sizeof(old_room_number) - 1] = '\0';
        FILE *rooms_file = fopen(pusers2, "r");
        if (rooms_file == NULL)
        {
            printf("Error opening rooms file\n");
            exit(1);
        }
        char room_lines[500][300];
        int room_line_count = 0;
        while (fgets(room_lines[room_line_count], sizeof(room_lines[room_line_count]), rooms_file) && 
               room_line_count < 500)
        {
            room_line_count++;
        }
        fclose(rooms_file);

        char new_room_number[100] = "";
        int found_new_room = 0;

        for (int i = 0; i < room_line_count; i++)
        {
            char curr_room[100] = "";
            char curr_status[20] = "";
            char curr_category[100] = "";
            char curr_price[100] = "";
            char line_copy[300];
            
            strncpy(line_copy, room_lines[i], sizeof(line_copy) - 1);
            line_copy[sizeof(line_copy) - 1] = '\0';

            sscanf(line_copy, "%s %s %s %s", curr_room, curr_status, curr_category, curr_price);

            if (strcmp(curr_room, old_room_number) == 0)
            {
                snprintf(room_lines[i], sizeof(room_lines[i]), "%s Available %s %s\n", 
                        curr_room, curr_category, curr_price);
            }
            else if (!found_new_room && strcmp(curr_category, selected_category) == 0 && 
                     strcmp(curr_status, "Available") == 0)
            {
                strncpy(new_room_number, curr_room, sizeof(new_room_number) - 1);
                new_room_number[sizeof(new_room_number) - 1] = '\0';
                snprintf(room_lines[i], sizeof(room_lines[i]), "%s Reserved %s %s\n", 
                        curr_room, curr_category, curr_price);
                found_new_room = 1;
            }
        }

        if (!found_new_room)
        {
            printf("No available rooms in the requested category.\n");
            return;
        }

        rooms_file = fopen(pusers2, "w");
        if (rooms_file == NULL)
        {
            printf("Error opening rooms file for writing\n");
            return;
        }

        for (int i = 0; i < room_line_count; i++)
        {
            fputs(room_lines[i], rooms_file);
        }
        fclose(rooms_file);

        strncpy(hold[1], new_room_number, 99);
        hold[1][99] = '\0';
        printf("Room category updated successfully\n");
        break;

    case 5:
        printf("Enter new number of nights:\n");
        fgets(new_value, sizeof(new_value), stdin);
        new_value[strcspn(new_value, "\n")] = '\0';
        int nights = atoi(new_value);
        if (nights < 1 || nights > 31)
        {
            printf("Invalid number of nights (1-31)\n");
            break;
        }
        printf("Are you sure you want to edit the number of nights? (Y/N): ");
        do
        {
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                printf("Reservation updated successfully\n");
                break;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Edit cancelled\n");
                return;
            }
            else
            {
                printf("Invalid choice, please try again\n");
            }
        } while (1);
        strncpy(hold[5], new_value, 99);
        hold[5][99] = '\0';
        break;
    case 6:
        printf("Enter new phone number:\n+2");
        do 
        {
            fgets(new_value, sizeof(new_value), stdin);
            new_value[strcspn(new_value, "\n")] = '\0';
            if (strlen(new_value) != 11)
            {
                printf("Invalid phone number (11 digits)\n+2");
            }
        } while (strlen(new_value) != 11);
        
        
        printf("Are you sure you want to change your phone number? (Y/N): ");
        do
        {
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                printf("Reservation updated successfully\n");
                break;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Edit cancelled\n");
                return;
            }
            else
            {
                printf("Invalid choice, please try again\n");
            }
        } while (1);
        strncpy(hold[8], new_value, 99);
        hold[8][99] = '\0';
        break;
    default:
        printf("Invalid choice, please try again\n");
        break;
    }

    // Create updated line
    char updated_line[1000] = "";
    for (int i = 0; i < counter_tokenising; i++)
    {
        strncat(updated_line, hold[i], sizeof(updated_line) - strlen(updated_line) - 2);
        if (i < counter_tokenising - 1)
        {
            strncat(updated_line, ",", sizeof(updated_line) - strlen(updated_line) - 1);
        }
    }
    strncat(updated_line, "", sizeof(updated_line) - strlen(updated_line) - 1);

    // Copy updated line to lines array
    if (matched_line != -1) {
    strncpy(lines[matched_line], updated_line, sizeof(lines[matched_line]) - 1);
    lines[matched_line][sizeof(lines[matched_line]) - 1] = '\0';
    }
    // Write back to file
    reservation_file = fopen(pusers1, "w");
    if (reservation_file == NULL) {
        // Free allocated memory before returning
        for (int i = 0; i < token_count; i++) {
            free(hold[i]);
        }
        free(hold);
        printf("Error updating file\n");
        return;
    }
    // Write all lines back to the file
    for (int i = 0; i < line_count; i++)
    {
        fputs(lines[i], reservation_file);
        if (!strchr(lines[i], '\n'))
        { // Add newline if not present
            fputc('\n', reservation_file);
        }
    }
    fclose(reservation_file);
    // Free allocated memory
    for (int i = 0; i < token_count; i++)
    {
        free(hold[i]);
    }
    free(hold);
    setConsoleColor(15);
}
