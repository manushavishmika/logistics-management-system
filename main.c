#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 300


void showMainMenu()
{
    int userChoice;

    do
    {
        printf("\n========================================\n");
        printf("    LOGISTICS MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Add New City\n");
        printf("2. Set Distance Between Cities\n");
        printf("3. View Distance Table\n");
        printf("4. Create New Delivery\n");
        printf("5. Exit Program\n");
        printf("----------------------------------------\n");
        printf("Your choice: ");
        scanf("%d", &userChoice);

        switch(userChoice)
        {
        case 1:
            addCity();
            break;
        case 2:
            editDistance();
            break;
        case 3:
            displayDistanceTable();
            break;
        case 4:
            addDelivery();
            break;
        case 5:
            printf("Thanks for using our system! Goodbye.\n");
            break;
        default:
            printf("Invalid choice! Please select 1-5.\n");
        }
    }
    while(userChoice != 5);
}

