#pragma once

// Disable the warning for using certain functions
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to remove a booking from a file
void removeBooking() {
    FILE* fptr, * fptr2;
    int bookingNo;
    char date[10] = "", filename[32], bookingNoString[20] = "", input[1024];

    // Input the booking number to be deleted
    printf("\n\nEnter the booking number to delete:\n");
    scanf("%d", &bookingNo);

    // Input the date of the booking
    printf("\n\nEnter the date the booking was made for:\n");
    getchar();  // Consume the newline character left by the previous input
    fgets(date, sizeof(date), stdin);

    size_t length = strlen(date);
    if (length > 0 && date[length - 1] == '\n') {
        date[length - 1] = '\0';
    }

    // Construct the filename based on the date
    snprintf(filename, sizeof(filename), "%s.txt", date);

    // Open the original file for reading
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        // Handle the case where the file cannot be opened
        printf("\n\nError opening file %s. Either the file does not exist or there was an issue.\n", filename);
        return;
    }

    // Open a temporary file for writing
    fptr2 = fopen("temp.txt", "w");
    if (fptr2 == NULL) {
        // Handle the case where the temporary file cannot be opened
        printf("\n\nError opening file for writing. Either the file does not exist or there was an issue.\n");
        fclose(fptr);
        return;
    }

    // Flag to indicate whether the current line is part of the booking to be removed
    int isInBooking = 0;

    // Loop through each line in the original file
    while (fgets(input, sizeof(input), fptr)) {
        // Check if the line contains the booking number
        char* bookingNumberStart = strstr(input, "Booking Number: ");
        if (bookingNumberStart != NULL) {
            // Extract the booking number from the line
            int extractedBookingNo;
            sscanf(bookingNumberStart + 16, "%d", &extractedBookingNo);

            // Check if the extracted booking number matches the target booking number
            if (extractedBookingNo == bookingNo) {
                // If this line contains the booking number, set the flag
                isInBooking = 1;
            }
        }

        // If the line is not part of the booking to be removed, write it to the temporary file
        if (!isInBooking) {
            fputs(input, fptr2);
        }

        // Check for the end of the booking (empty line)
        if (input[0] == '\n') {
            // Reset the flag when the end of the booking is reached
            isInBooking = 0;
        }
    }

    // Close the files
    fclose(fptr);
    fclose(fptr2);

    // Remove the original file
    remove(filename);

    // Rename the temporary file to the original filename
    rename("temp.txt", filename);

    // Display a success message
    printf("\n\nBooking %d has been removed successfully.\n", bookingNo);
}
