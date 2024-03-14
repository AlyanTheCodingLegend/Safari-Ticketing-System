#pragma once

#pragma warning(disable:4996)


#include <stdio.h>
#include <stdlib.h>

// Function to display contents of a booking file based on date
void DisplayBookingFileContents() {
    char filename[20];  // Assuming the date format is YYYYMMDD and adding .txt
    char date[9];

    printf("Enter the date (DDMMYYYY) to show details for: ");
    scanf("%8s", date);

    snprintf(filename, sizeof(filename), "%s.txt", date);

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("\n\nError opening file %s. Either the file does not exist or there was an issue.\n", filename);
        return;
    }

    printf("\n\nContents of Booking File for Date %s:\n", date);
    printf("-----------------------------------------------------------------------------------\n");

    char c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    printf("\n-----------------------------------------------------------------------------------\n");

    fclose(file);
}