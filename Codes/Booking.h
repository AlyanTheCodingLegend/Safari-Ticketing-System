#pragma once

#pragma warning(disable: 4996)  // Disable the safety warning for using certain functions

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void Validator(int* valPtr, int lower, int upper);  // Function prototype for input validation

int ticketCounter[8] = { 0,0,0,0,0,0,0,0 };  // Array to keep track of the total number of each type of ticket booked

// Function to take inputs for booking tickets
void InputTickets(int i, int* ticketTypePtr, int* ticketNumberPtr, char* dayNightPtr, int isFirst) {

    printf("Enter the number of the type of ticket you wish to book:\n\n");
    scanf("%d", ticketTypePtr + i);

    // Validate the ticket type input

    if (isFirst == 1) {
        Validator(ticketTypePtr + i, 1, 5);
    }
    else {
        Validator(ticketTypePtr + i, 6, 8);
    }

    printf("\nEnter the quantity of tickets you wish to book. You can book 50 at one time or 10 family tickets at one time:\n\n");
    scanf("%d", ticketNumberPtr + i);


    // Special handling for family and 6+ people tickets
    if (*(ticketTypePtr + i) == 5) {
        Validator(ticketNumberPtr + i, 6, 50);
    }
    else if (*(ticketTypePtr + i) == 4) {
        Validator(ticketNumberPtr + i, 1, 10);
    }
    else {
        Validator(ticketNumberPtr + i, 1, 50);
    }

    // Update ticketCounter array with the booked ticket quantity
    *(ticketCounter + *(ticketTypePtr + i) - 1) += *(ticketNumberPtr + i);

    // For certain ticket types, ask for the type of ticket (12-hour or 24-hour)
    if (*(ticketTypePtr + i) > 0 && *(ticketTypePtr + i) < 6) {
        int hourType;
        printf("\nEnter type of ticket\n1 for 12-hour\n2 for 24-hour\n  ");
        scanf("%d", &hourType);
        Validator(&hourType, 1, 2);
        if (hourType == 1) {
            *(dayNightPtr + i) = '1';
        }
        else {
            *(dayNightPtr + i) = '2';
        }
    }
    else {
        *(dayNightPtr + i) = '-';
    }
}

// Function to calculate the total cost of each item
void CalculateTotal(int i, int ticketTypes[], int ticketNumbers[], int ticketPrice[8][2], int* TotalPtr, char dayNight[]) {
    int j = 0;

    // For certain ticket types, determine if it's day or night
    if (ticketTypes[i] > 0 && ticketTypes[i] < 6) {
        if (dayNight[i] == '2') {
            j = 1;
        }
    }

    // Calculate the total cost based on ticket type, quantity, and time
    *(TotalPtr + i) = ticketPrice[ticketTypes[i] - 1][j] * ticketNumbers[i];
}

// Function to display the booking details
void DisplayBooking(int length, int ticketTypes[], int ticketNumbers[], char dayNight[], int ticketTotals[], int BookinNo) {
    int sum = 0;
    printf("\n\nBooking Number:  %d\n", BookinNo);
    printf("S No.\tTicket Type\tNumber\t12/24\tTotal\n");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        printf("%d.\t", i + 1);
        switch (ticketTypes[i]) {
        case 1:
            printf("Adult\t");
            break;
        case 2:
            printf("Child\t");
            break;
        case 3:
            printf("Senior\t");
            break;
        case 4:
            printf("Family\t");
            break;
        case 5:
            printf("6+ People");
            break;
        case 6:
            printf("Lion Feeding ");
            break;
        case 7:
            printf("Peng Feeding");
            break;
        case 8:
            printf("Evening BBQ ");
            break;
        }

        printf("\t%d\t", ticketNumbers[i]);

        // Check for '1' and '2' in dayNight and display corresponding strings
        if (dayNight[i] == '1') {
            printf("12\t");
        }
        else if (dayNight[i] == '2') {
            printf("24\t");
        }
        else {
            printf("--\t");
        }

        printf("%d\n", ticketTotals[i]);

        sum += ticketTotals[i];
    }

    printf("\t\t\t\t\t%d", sum);

    printf("\n\nMake sure to note down your booking number!!");
}



// Function to suggest better booking options
void EnsureBestBooking(int length, int ticketTypes[], int ticketNumbers[]) {
    int totalIndividualTickets = 0;
    for (int i = 0; i < 3; i++) {
        totalIndividualTickets += ticketCounter[i];
    }

    // Suggest type 5 ticket for groups of 6 or more
    if (totalIndividualTickets >= 6) {
        printf("\nYou can buy type 5 ticket and avail 6+ people discount\n");
    }

    // Suggest type 4 family ticket for specific combinations of individual tickets
    if ((ticketCounter[0] + ticketCounter[2] >= 2) && (ticketCounter[1] >= 3)) {
        printf("\nYou can buy type 4 family ticket and get better value.\n");
    }
}




// Function to store booking details in a file
void StoreBookingDetails(int BookingNumber, int ticketTypes[], int ticketNumbers[], char dayNight[], int ticketTotals[], int length) {
    FILE* file;
    char filename[20]; // Assuming the date format is YYYYMMDD and adding .txt
    char date[9];
    int sum = 0;

    printf("Enter the date you want to make the booking for (DDMMYYYY): ");
    getchar();
    scanf("%8s", date);

    snprintf(filename, sizeof(filename), "%s.txt", date);

    // Open the file in append mode or create a new file if it doesn't exist
    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write booking details to the file
    fprintf(file, "Booking Number: %d\n", BookingNumber);
    fprintf(file, "S No.\tTicket Type\tNumber\t12/24\tTotal\n");
    fprintf(file, "-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < length; i++) {
        fprintf(file, "%d\t", i + 1);
        switch (ticketTypes[i]) {
        case 1:
            fprintf(file, "Adult\t");
            break;
        case 2:
            fprintf(file, "Child\t");
            break;
        case 3:
            fprintf(file, "Senior\t");
            break;
        case 4:
            fprintf(file, "Family\t");
            break;
        case 5:
            fprintf(file, "6+_people");
            break;
        case 6:
            fprintf(file, "Lion_feeding ");
            break;
        case 7:
            fprintf(file, "Peng_feeding");
            break;
        case 8:
            fprintf(file, "Evening_bbq");
            break;
        }

        fprintf(file, "\t%d\t", ticketNumbers[i]);

        switch (dayNight[i]) {
        case('1'):
            fprintf(file, "12\t");
            break;
        case('2'):
            fprintf(file, "24\t");
            break;
        default:
            fprintf(file, "--\t");
            break;
        }

        fprintf(file, "%d\n", ticketTotals[i]);

        sum += ticketTotals[i];
    }

    fprintf(file, "\t\t\t\t\t%d\n\n", sum);

    // Close the file
    fclose(file);

    printf("Booking details have been successfully stored in %s\n", filename);
}

// Function to book tickets and handle the entire booking process
void bookTickets(int BookingNumber) {
    int ticketPrice[8][2] = {
        {2000, 3000},
        {1000, 2000},
        {1500, 2500},
        {6000, 9000},
        {1000, 2000},
        {250, 0},
        {200, 0},
        {500, 0}
    };

    int* ticketTypes;
    int* ticketNumbers;
    char* dayNight;
    int* ticketTotals;

    int confirm = 0;
    while (confirm == 0) {
        int i = 0;
        char choice = 'y';

        // Dynamically allocate memory for arrays
        ticketTypes = (int*)malloc(sizeof(int));
        ticketNumbers = (int*)malloc(sizeof(int));
        dayNight = (char*)malloc(sizeof(char));
        ticketTotals = (int*)malloc(sizeof(int));

        while (choice == 'y') {
            printf("\n\nInput your main tickets from serial number 1 to 5:\n  ");
            InputTickets(i, ticketTypes, ticketNumbers, dayNight, 1);
            CalculateTotal(i, ticketTypes, ticketNumbers, ticketPrice, ticketTotals, dayNight);

            i++;

            // Dynamically reallocate memory for arrays
            ticketTypes = (int*)realloc(ticketTypes, (i + 1) * sizeof(int));
            ticketNumbers = (int*)realloc(ticketNumbers, (i + 1) * sizeof(int));
            dayNight = (char*)realloc(dayNight, (i + 1) * sizeof(char));
            ticketTotals = (int*)realloc(ticketTotals, (i + 1) * sizeof(int));

            printf("\n\nDo you want to add more things to the cart? Enter y to do so, else enter any other value:\n");
            getchar();
            scanf("%c", &choice);

            choice = tolower(choice);
        }

        printf("Do you want to add additional activities? Enter y to do so.");
        getchar();
        scanf("%c", &choice);
        tolower(choice);

        while (choice == 'y') {
            printf("\n\nInput your additional tickets from serial number 6 to 8:\n");
            InputTickets(i, ticketTypes, ticketNumbers, dayNight, 0);
            CalculateTotal(i, ticketTypes, ticketNumbers, ticketPrice, ticketTotals, dayNight);

            i++;

            // Dynamically reallocate memory for arrays
            ticketTypes = (int*)realloc(ticketTypes, (i + 1) * sizeof(int));
            ticketNumbers = (int*)realloc(ticketNumbers, (i + 1) * sizeof(int));
            dayNight = (char*)realloc(dayNight, (i + 1) * sizeof(char));
            ticketTotals = (int*)realloc(ticketTotals, (i + 1) * sizeof(int));

            printf("\n\nDo you want to add more additional activities to the cart? Enter y to do so:\n");
            getchar();
            scanf("%c", &choice);

            choice = tolower(choice);
        }

        printf("\n-----------------------------------------------------------------------------------\n");
        printf("\nYour booking summary.\n\n");
        DisplayBooking(i, ticketTypes, ticketNumbers, dayNight, ticketTotals, BookingNumber);
        printf("\n\n");
        EnsureBestBooking(i, ticketTypes, ticketNumbers);



        printf("\n\nDo you confirm your booking?\nPress 1 to proceed. Press 0 to make a different booking:\n");
        scanf("%d", &confirm);
        Validator(&confirm, 0, 1);

        if (confirm == 1) {
            // Assuming 'date' is a string containing the current date in the format YYYYMMDD
            StoreBookingDetails(BookingNumber, ticketTypes, ticketNumbers, dayNight, ticketTotals, i);
        }

        // Free dynamically allocated memory
        free(ticketTypes);
        free(ticketNumbers);
        free(dayNight);
        free(ticketTotals);
    }

    printf("\n\nYour ticket has been booked successfully. Thank you for your patience.\n");
}
