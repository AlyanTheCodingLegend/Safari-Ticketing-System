#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Booking.h"
#include "displayFile.h"
#include "removeBooking.h"
#include "getSummary.h"

void Validator(int* valPtr, int lower, int upper);

int main()
{


	
	int n = 1,date;
	int option;

	

	// head using ASCII art
	printf("\n\n");
	printf("        |||                --------------------------------------------------------\n");
	printf("        / \\__              |         ***    *    *****   *    *****  *****        |         /\\_/\\                \n");
	printf("        (    @\\___         |        *      * *   *      * *   *   *    *          |        /     \\              \n");   
	printf("        /         O        |         **   *****  ***   *****  *****    *          |        ( o.o )               \n");
	printf("        /   (_____/        |           *  *   *  *     *   *  *  *     *          |          |||                   \n");
	printf("    /_____/       U        |        ****  *   *  *     *   *  *   *  *****        |         > ^ <               \n");
	printf("                           --------------------------------------------------------\n\n");

	
	
	printf("Embark on luxury and wildlife harmony at our Lavish Safari Park.\n Seamless bookings, exotic encounters where opulence meets the untamed.\n Welcome to the epitome of adventure in nature's embrace.\n\n");

	printf("Welcome to the safari booking system.\nEnter the date today(DDMMYYYY):\n");
	scanf("%d", &date);

	n += date * 10;

	for (;;) {
		system("clear");
		
		

		// head using ASCII art
		printf("\n\n");
		printf("        |||                --------------------------------------------------------\n");
		printf("        / \\__              |         ***    *    *****   *    *****  *****        |         /\\_/\\                \n");
		printf("        (    @\\___         |        *      * *   *      * *   *   *    *          |        /     \\              \n");
		printf("        /         O        |         **   *****  ***   *****  *****    *          |        ( o.o )               \n");
		printf("        /   (_____/        |           *  *   *  *     *   *  *  *     *          |          |||                   \n");
		printf("    /_____/       U        |        ****  *   *  *     *   *  *   *  *****        |         > ^ <               \n");
		printf("                           --------------------------------------------------------\n\n");

		
		printf("Embark on luxury and wildlife harmony at our Lavish Safari Park.\n Seamless bookings, exotic encounters where opulence meets the untamed.\n Welcome to the epitome of adventure in nature's embrace.\n\n");
		
		printf("\n-----------------------------------------------------------------------------------\n\n\n");
		printf("How can I help you today? Enter a number to indicate your choice.\n\n");
		printf("1. Book a ticket\n");
		printf("2. See bookings on a certain date\n");
		printf("3. Delete a booking\n");
		printf("4. Get a summary for a certain date\n");
		printf("0. Exit\n\n");
		
		scanf("%d", &option);
		Validator(&option, 0, 4);

		switch (option) {
		case(1):
			displayMenu();
			bookTickets(n);
			n++;
			break;
		case(2):
			DisplayBookingFileContents();
			break;
		case(3):
			removeBooking();
			break;
		case(4):
			getSummary();
			break;
		default:
			break;
		}

		
		if (option == 0) {
			return 0;
		}

		getchar();
		getchar();



	}
}


