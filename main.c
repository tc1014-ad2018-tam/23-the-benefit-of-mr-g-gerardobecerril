/*
 * This program was created as a system for an event that will take place on september 26th, 2020, in benefit of Mr. G.
 * It allows the user to sell tickets, save data, create reports and exit the program.
 *
 * Author: Gerardo González Becerril.
 * Date: November 3rd, 2018.
 * E-mail: a01411981@itesm.mx
 */

// Libraries needed.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// This structure saves all the information required for a ticket; whether the seat is taken, the payment method used,
// the name of the buyer and the cost of the seat.
struct seatInformation {
    bool isOccupied;
    char paymentMethod[20];
    char name[50];
    int cost;
};

// This function simply prints the zones and prices.
void displayPrices() {
    printf("A. VIP: $100\nB. Platinum: $85\nC. Gold: $70\nD. Silver: $55\nE. Green: $45\nF. Yellow: $40\n");
    printf("G. Red: $30\nH. Sky Blue: $50\nI. Navy Blue: $35\nJ. Deep Blue: $20\n");
}

// This function asks the user for a number for a row or sit in one of two ranges, which are determined by the user.
// It then returns that number.
int selectWingSeat(int minimum, int maximum, int minimum2, int maximum2, char type[10]) {
    int num;

    do {
        printf("Please select a %s for your seat.\n", type);
        printf("Number must be between %d and %d, or %d and %d.\n", minimum, maximum, minimum2, maximum2);
        scanf("%d", &num);
    } while ((num < minimum || num > maximum) && (num < minimum2 || num > maximum2));

    return num;
}

// This function works exactly like the last function, except there is only one range.
int selectCentralSeat(int minimum, int maximum, char type[10]) {
    int num;

    do {
        printf("Please select a number for your %s.\n", type);
        printf("Number must be between %d and %d.\n", minimum, maximum);
        scanf("%d", &num);
    } while (num < minimum || num > maximum);

    return num;
}

// This function displays prices and then asks the user for a zone, which it then finally returns.
char askForZone() {
    char zone;

    displayPrices();

    do {
        printf("Please select a zone by entering the respective letter.\n");
        scanf(" %c", &zone);
    } while (zone != 'A' && zone != 'B' && zone != 'C' && zone != 'D' && zone != 'E' && zone != 'F' && zone != 'G' && zone != 'H' && zone != 'I' && zone != 'J');

    return zone;
}

// This function uses function to take a zone as an input, then, depending on the selected zone, asks the user for a
// seat determining the correct limits and finally, adding the correct cost of the seat.
void askForSit(int *row, int *seat, int *cost, char zone) {

    switch(zone) {

        case 'A':
            *row = selectCentralSeat(1, 5, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 100;
            break;

        case 'B':
            *row = selectCentralSeat(6, 10, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 85;
            break;

        case 'C':
            *row = selectCentralSeat(11, 50, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 70;
            break;

        case 'D':
            *row = selectCentralSeat(51, 100, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 55;
            break;

        case 'E':
            *row = selectCentralSeat(101, 250, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 45;
            break;

        case 'F':
            *row = selectCentralSeat(251, 350, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 40;
            break;

        case 'G':
            *row = selectCentralSeat(351, 400, "row");
            *seat = selectCentralSeat(51, 150, "seat");
            *cost = 30;
            break;

        case 'H':
            *row = selectCentralSeat(1, 100, "row");
            *seat = selectWingSeat(1, 50, 151, 200, "seat");
            *cost = 50;
            break;

        case 'I':
            *row = selectCentralSeat(101, 300, "row");
            *seat = selectWingSeat(1, 50, 151, 200, "seat");
            *cost = 35;
            break;

        default:
            *row = selectCentralSeat(301, 400, "row");
            *seat = selectWingSeat(1, 50, 151, 200, "seat");
            *cost = 20;

    }

}

// This function checks whether the 'isOccupied' variable is true or false for a certain seat. If it's not, it
// changes it to true, then informs the user and returns true; if it is, it also informs the user, but returns false.
bool checkAvailability(int row, int seat, struct seatInformation seats[400][200]) {

    if (!seats[row-1][seat-1].isOccupied) {
        seats[row-1][seat-1].isOccupied = true;
        printf("Your purchase has been successful!\n");
        return true;
    } else {
        printf("Sadly, that sit was already taken by %s.\n", seats[row-1][seat-1].name);
        return false;
    }

}

// This function asks the user for his name, then saves it right into the seat's 'name' variable. Then, it asks the
// user for a paying method and adds the selected method to the seat's 'paymentMethod' variable.
void askForInformation(int row, int seat, struct seatInformation seats[400][200]) {

    char method;

    printf("What is your name?\n");
    fgets(seats[row-1][seat-1].name, sizeof(seats[row-1][seat-1].name), stdin);
    fflush(stdin);
    fgets(seats[row-1][seat-1].name, sizeof(seats[row-1][seat-1].name), stdin);
    strtok(seats[row-1][seat-1].name, "\n");

    printf("How would you be paying?\n");
    printf("A. Visa\nB. Mastercard\nC. American Express.\n");

    do {
        printf("Select an option by entering the letter.\n");
        scanf(" %c", &method);
    } while (method != 'A' && method != 'B' && method != 'C');

    switch(method) {

        case 'A':
            strcpy(seats[row-1][seat-1].paymentMethod, "Visa");
            break;

        case 'B':
            strcpy(seats[row-1][seat-1].paymentMethod, "Mastercard");
            break;

        default:
            strcpy(seats[row-1][seat-1].paymentMethod, "American Express");

    }

}

// Declaring 'sellATicket' function.
bool sellATicket(int row, int seat, struct seatInformation seats[400][200], bool shouldAskForZone, char zone, bool hasSavedData);

// This function asks the user what he would like to do next and is called only when his desired seat is occupied.
// It can call the 'sellATicket' function again, but not asking for a zone. It can call it asking for another zone or
// it can end the function.
int whatNext(int row, int seat, struct seatInformation seats[400][200], char zone, bool hasSavedData) {

    char nextMove;

    printf("What would you like to do now?\n");
    printf("A. Buy another seat in the same zone.\nB. Select another zone.\nC. Go back to menu.\n");

    do {
        printf("Select an option by entering the letter.\n");
        scanf(" %c", &nextMove);
    } while (nextMove != 'A' && nextMove != 'B' && nextMove != 'C');

    switch(nextMove) {

        case 'A':
            sellATicket(row, seat, seats, false, zone, hasSavedData);
            break;

        case 'B':
            sellATicket(row, seat, seats, true, zone, hasSavedData);
            break;

        default:
            return 0;

    }

    return 1;

}

// This function can let the input determine whether it'll ask for a zone or if it'll be provided by the input.
// Depending on this, it can call the 'askForZone' function within the 'askForSit' function. Then it uses the
// 'checkAvailability' function with the selected row and seat and either adds the correct cost to the 'cost' variable
// in the seat, asks for the user's other information and informs him of this. The return values are used for a
// function called 'hasSavedData', which indicates whether data has been saved. Any new sale means there's new data
// that hasn't been saved, so if a sale is successful, it returns true; if it isn't, false.A
bool sellATicket(int row, int seat, struct seatInformation seats[400][200], bool shouldAskForZone, char zone, bool hasSavedData) {

    int cost;

    printf("Hello there! So you would to purchase a ticket, huh?\n");

    if (shouldAskForZone) {
        printf("Prices for each zone:\n");
        askForSit(&row, &seat, &cost, askForZone());
    }  else {
        askForSit(&row, &seat, &cost, zone);
    }

    if (checkAvailability(row, seat, seats)) {
        seats[row-1][seat-1].cost = cost;
        askForInformation(row, seat, seats);
        printf("Fantastic! Your ticket will be bought via %s, %s. Come back soon!\n", seats[row-1][seat-1].paymentMethod, seats[row-1][seat-1].name);
        return false;
    } else {
        if (whatNext(row, seat, seats, zone, hasSavedData) == 0) {
            if (hasSavedData) {
                return true;
            } else {
                return false;
            }
        }
    }

    return false;

}


// This function creates a new file, opens one, then checks whether it's empty to prevent errors. It then loops 400
// times to add all of the information currently stores in the 'seats' array into the file. Finally, it closes the file.
bool saveData(struct seatInformation seats[400][200]) {

    printf("Saving data...\n");

    FILE *f1;
    f1 = fopen("mrGFile.txt", "wb");

    if (f1 == NULL) {
        printf("An error has occurred.\n");
        exit(1);
    }

    for (int i = 0; i < 400; i++) {
        fwrite(seats[i], sizeof(struct seatInformation), sizeof(seats[i]), f1);
    }

    fclose(f1);

    printf("\nYour data has been saved successfully!\n");

    return true;
}

// This function is used to set all the isOccupied booleans to false in a file.
void resetSeats(struct seatInformation seats[400][200]) {
    printf("Initializing to 0...\n");
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 200; j++) {
            seats[i][j].isOccupied = false;
        }
    }
    saveData(seats);
}

// This function creates a new file, opens one, then checks whether it's empty to prevent errors. It then loops 400
// times to read all of the seats' information and add it to the 'seats' array. Finally, it closes the file.
void readData(struct seatInformation seats[400][200]) {

    FILE *f1;
    f1 = fopen("mrGFile.txt", "rb");

    if (f1 == NULL) {
        printf("An error has occurred.\n");
        exit(1);
    }

    for (int i = 0; i < 400; i++) {
        fread(seats[i], sizeof(struct seatInformation), sizeof(seats[i]), f1);
    }

    fclose(f1);

}

// There are four ways this function can work, depending on the boolean variables of the input. It, first, uses loops
// to go from a selected start to a selected ending to go through the seats matrix. Then, it checks whether the
// current seat is occupied, and if it is, it can either add the cost of the seat to the total or add 1 to the total,
// depending on what the function is for. In both cases, 'total' is initialized to 0. Next, it can optionally do a second
// loop, which is used when a section has two areas. Finally, it returns the 'total' variable.
float totalSales(struct seatInformation seats[400][200], int rowStart, int rowEnd, int seatStart, int seatEnd, int seatStart2, int seatEnd2, bool hasTwoAreas, bool getIncome) {

    int total = 0;

    for (int i = rowStart; i < rowEnd; i++) {

        for (int j = seatStart; j < seatEnd; j++) {

            if (seats[i][j].isOccupied) {

                if (getIncome) {
                    total += seats[i][j].cost;
                } else {
                    total++;
                }

            }

        }

    }

    if (hasTwoAreas) {

        for (int i = rowStart; i < rowEnd; i++) {

            for (int j = seatStart2; j < seatEnd2; j++) {

                if (seats[i][j].isOccupied) {

                    if (getIncome) {
                        total += seats[i][j].cost;
                    } else {
                        total++;
                    }

                }

            }

        }

    }

    return total;

}

// This function asks for a zone, then depending on which one was selected, determines several values for limits,
// which are meant to be used in the 'totalSales' function. It initializes 'seatStart2' to 0, which is never the case
// if the selected zone requires this variable. As such, at the very end, it checks whether the 'seatStart2' variable
// was changed. If it was, then it needs one. If it wasn't, it doesn't. It returns the 'total', as well.
float totalSalesPerZone(struct seatInformation seats[400][200], bool getIncome) {

    char zone = askForZone();
    int rowStart;
    int rowEnd;
    int seatStart;
    int seatEnd;
    int seatStart2 = 0;
    int seatEnd2 = 0;
    float total;

    switch(zone) {

        case 'A':
            rowStart = 0;
            rowEnd = 5;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'B':
            rowStart = 5;
            rowEnd = 10;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'C':
            rowStart = 10;
            rowEnd = 50;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'D':
            rowStart = 50;
            rowEnd = 100;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'E':
            rowStart = 100;
            rowEnd = 250;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'F':
            rowStart = 250;
            rowEnd = 350;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'G':
            rowStart = 350;
            rowEnd = 400;
            seatStart = 50;
            seatEnd = 150;
            break;

        case 'H':
            rowStart = 0;
            rowEnd = 100;
            seatStart = 0;
            seatEnd = 50;
            seatStart2 = 150;
            seatEnd2 = 200;
            break;

        case 'I':
            rowStart = 100;
            rowEnd = 300;
            seatStart = 0;
            seatEnd = 50;
            seatStart2 = 150;
            seatEnd2 = 200;
            break;

        default:
            rowStart = 300;
            rowEnd = 400;
            seatStart = 0;
            seatEnd = 50;
            seatStart2 = 150;
            seatEnd2 = 200;

    }

    if (seatStart2 == 0) {
        total = totalSales(seats, rowStart, rowEnd, seatStart, seatEnd, 0, 0, false, getIncome);
    } else {
        total = totalSales(seats, rowStart, rowEnd, seatStart, seatEnd, seatStart2, seatEnd2, true, getIncome);
    }

    return total;

}

// This function displays a menu for reports. It displays the user's options, then asks for one. It uses cases to
// determine which function will be needed. For the two last cases, it gets the amount of seats sold, then multiplies
// it by 100 and divides it by 80000 (the number of seats in the theatre) to get the occupation rate.
void reportMenu(struct seatInformation seats[400][200]) {

    char selection;
    float total;

    printf("Alright! This is the reports section.\nThese is the information we can provide.\n");
    printf("A. Total tickets sold.\nB. Total tickets sold per zone.\nC. Total income.\n");
    printf("D. Total income per zone.\nE. Occupation rate.\nF. Occupation rate per zone.\n");

    do {
        printf("Select an option.\n");
        scanf(" %c", &selection);
    } while (selection != 'A' && selection != 'B' && selection != 'C' && selection != 'D' && selection != 'E' && selection != 'F');

    switch(selection) {

        case 'A':
            total = totalSales(seats, 0, 400, 0, 200, 0, 0, false, false);
            printf("REPORT:\nTotal tickets sold: %0g.\n", total);
            break;

        case 'B':
            total = totalSalesPerZone(seats, false);
            printf("REPORT:\nTotal tickets sold in this zone: %g.\n", total);
            break;

        case 'C':
            total = totalSales(seats, 0, 400, 0, 200, 0, 0, false, true);
            printf("REPORT:\nTotal income: $%.02f.\n", total);
            break;

        case 'D':
            total = totalSalesPerZone(seats, true);
            printf("REPORT:\nTotal income in this zone: $%.02f.\n", total);
            break;

        case 'E':
            total = totalSales(seats, 0, 400, 0, 200, 0, 0, false, false);
            printf("REPORT:\nOccupation rate: %g%c.\n", total*0.00125, 37);
            break;

        default:
            total = totalSalesPerZone(seats, false);
            printf("REPORT:\nOccupation rate in this zone: %g%c.\n", total*0.00125, 37);

    }

}

// This function displays the user's options, then asks for one. A 'hasSavedData' variable was created to determine
// whether the user had already saved new data. It's initialized to true in the main function, since no new data's
// created when the system starts. It grabs the return values from the 'sellATicket' function when said option is
// selected. This value's true when a purchase was successful and false when it wasn't, since a sale would mean new
// data which hasn't been saved. If the user selects the second option, the 'hasSavedData' variable will be true, the
// return value of the 'saveData' function, since the data will now be saved. The last option checks whether data has
// been saved in order to know whether the system can or cannot stop.
void mainMenu(struct seatInformation seats[400][200], bool *hasSavedData) {

    char option;
    int row = 0;
    int seat = 0;
    char zone = 'A';

    printf("\nWelcome to the Mr. G System! These are the following tasks you can carry out.\n");
    printf("A. Sell a Ticket.\nB. Save data.\nC. Report.\nD. Exit.\n");

    do {
        printf("Select an option.\n");
        scanf(" %c", &option);
    } while (option != 'A' && option != 'B' && option != 'C' && option != 'D');

    switch(option) {

        case 'A':
            *hasSavedData = sellATicket(row, seat, seats, true, zone, *hasSavedData);
            break;

        case 'B':
            *hasSavedData = saveData(seats);
            break;

        case 'C':
            reportMenu(seats);
            break;

        default:
            if (*hasSavedData) {
                printf("Thank you for using our system! Come back soon!\n");
                exit(0);
            } else {
                printf("You must save data first.\n");
            }

    }

}

// This function is for initializing new programs or reading previous ones. It can also reset a program. It is here
// because the program couldn't read a file with no information to add to the 'seats' matrix.
void beforeMenu(struct seatInformation seats[400][200]) {
    char userInput;

    printf("Welcome to the Mr. G System.\nIf this is the first time you're using this program, please enter 'N'.\n");
    printf("If this isn't and you wish to use the same data, enter any other letter.\n");
    printf("THIS IS REALLY IMPORTANT.\n");
    scanf(" %c", &userInput);

    if (userInput == 'N') {
        resetSeats(seats);
    } else {
        readData(seats);
    }

}

// Main function. It creates the 'seats' matrix, initializes 'hasSavedData' to true, calls the 'beforeMenu' function
// and has the 'mainMenu' function on an infinite loop.
int main() {
    struct seatInformation seats[400][200];
    bool hasSavedData = true;

    beforeMenu(seats);

    while (1) {
        mainMenu(seats, &hasSavedData);
    }
}