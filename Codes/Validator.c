#pragma warning (disable: 4996)

#include <stdio.h>

// Function to validate an integer input within a specified range
// Parameters:
//   - valPtr: Pointer to the integer value to be validated
//   - lower: Lower bound of the valid range (inclusive)
//   - upper: Upper bound of the valid range (inclusive)
void Validator(int* valPtr, int lower, int upper) {
    // Keep prompting the user until a valid input is provided
    while (*valPtr < lower || *valPtr > upper) {
        printf("\nInvalid input! Please enter a value between %d and %d:\n", lower, upper);
        scanf("%d", valPtr);
    }
    // The loop exits only when a valid input is provided
}