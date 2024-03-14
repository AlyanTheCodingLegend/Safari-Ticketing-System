#pragma once

#pragma warning(disable:4996) // Disable the safety warning for using certain functions

#include <stdio.h>

// Procedure to display the menu information in a table
void displayMenu() {
    printf(" --------------------------------------------------------------------------\n");
    printf("| S No.  | Ticket Type          | 12-hour/Normal(Rs) |     24-hour(Rs)    |\n");
    printf(" --------------------------------------------------------------------------\n");
    printf("|   1    | One Adult            |        2000        |        3000        |\n");
    printf("|   2    | One Child            |        1000        |        2000        |\n");
    printf("|   3    | One Senior           |        1500        |        2500        |\n");
    printf("|   4    | Family Ticket        |        6000        |        9000        |\n");
    printf("|   5    | 6+ People            |        1000        |        2000        |\n");
    printf("|   6    | Lion Feeding         |         250        |           0        |\n");
    printf("|   7    | Penguin Feeding      |         200        |           0        |\n");
    printf("|   8    | Evening BBQ          |         500        |           0        |\n");
    printf(" --------------------------------------------------------------------------\n");
}


