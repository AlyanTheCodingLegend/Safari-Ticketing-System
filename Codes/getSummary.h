#pragma once

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structure to represent a ticket record
struct Ticket {
    int sNo;               // Serial number
    char ticketType[30];   // Type of ticket
    int ticketNumber;      // Number of tickets
    int ticketHourType;    // Type of ticket (e.g., 12-hour or 24-hour)
    int ticketTotal;       // Total cost for the ticket type
};

// Function to get the summary from a file
void getSummary() {
    struct Ticket ticketRecord;

    // Arrays to store ticket statistics
    int ticketNumbers[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int ticketTotals[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    char filename[20], date[10], string[164];
    int sum = 0;

    // Input date for which summary is needed
    printf("\n\nEnter date booking was made for (DDMMYYYY) to get summary:\n");
    getchar();
    fgets(date, sizeof(date), stdin);

    // Remove newline character from date
    size_t length = strlen(date);
    if (length > 0 && date[length - 1] == '\n') {
        date[length - 1] = '\0';
    }

    // Create filename based on date
    snprintf(filename, 20, "%s.txt", date);

    // Open the file for reading
    FILE* file = fopen(filename, "r");

    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    // Read data from the file
    while (fgets(string, sizeof(string), file)) {
        // Skip lines that do not start with a digit
        if (isdigit(string[0]) == 0) {
            continue;
        }

        // Parse the line to extract ticket information
        sscanf(string, "%d %s %d %d %d", &ticketRecord.sNo, ticketRecord.ticketType, &ticketRecord.ticketNumber, &ticketRecord.ticketHourType, &ticketRecord.ticketTotal);

        // Update ticket statistics based on ticket type
        if (strcmp(ticketRecord.ticketType, "Adult") == 0) {
            ticketNumbers[0] += ticketRecord.ticketNumber;
            ticketTotals[0] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Child") == 0) {
            ticketNumbers[1] += ticketRecord.ticketNumber;
            ticketTotals[1] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Senior") == 0) {
            ticketNumbers[2] += ticketRecord.ticketNumber;
            ticketTotals[2] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Family") == 0) {
            ticketNumbers[3] += ticketRecord.ticketNumber;
            ticketTotals[3] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "6+_people") == 0) {
            ticketNumbers[4] += ticketRecord.ticketNumber;
            ticketTotals[4] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Lion_feeding") == 0) {
            ticketNumbers[5] += ticketRecord.ticketNumber;
            ticketTotals[5] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Peng_feeding") == 0) {
            ticketNumbers[6] += ticketRecord.ticketNumber;
            ticketTotals[6] += ticketRecord.ticketTotal;
        }
        else if (strcmp(ticketRecord.ticketType, "Evening_bbq") == 0) {
            ticketNumbers[7] += ticketRecord.ticketNumber;
            ticketTotals[7] += ticketRecord.ticketTotal;
        }

        // Update the total sum
        sum += ticketRecord.ticketTotal;
    }

    // Close the file
    fclose(file);

    // Display the summary
    printf("\n\n");
    printf("| Ticket Type    | Tickets Sold | Total Price |\n");
    printf("-----------------------------------------------------------------------------------\n");

    for (int a = 0; a < 8; a++) {
        switch (a) {
        case 0:
            printf("Adult\t\t");
            break;
        case 1:
            printf("Child\t\t");
            break;
        case 2:
            printf("Senior\t\t");
            break;
        case 3:
            printf("Family\t\t");
            break;
        case 4:
            printf("6+_people\t");
            break;
        case 5:
            printf("Lion_feeding\t");
            break;
        case 6:
            printf("Peng_feeding\t");
            break;
        case 7:
            printf("Evening_bbq\t");
            break;
        }

        printf("\t%d\t\t%d\n", ticketNumbers[a], ticketTotals[a]);
    }

    printf("-----------------------------------------------------------------------------------\n");
    printf("Net Total: %d\n", sum);
}
