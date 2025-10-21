#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 300


typedef struct
{
    char name[50];
} City;

typedef struct
{
    char name[10];
    int capacity;
    float rate;
    float speed;
    float efficiency;  // km per liter

} Vehicle;

typedef struct
{
    int source;
    int destination;
    float weight;
    int vehicleType;
    float distance;
    float cost, fuelUsed, fuelCost, totalCost, profit, customerCharge, time;
} Delivery;

// Global variables
City cities[MAX_CITIES];
int distanceMatrix[MAX_CITIES][MAX_CITIES];
int cityCount = 0;
Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;

// Vehicle data
Vehicle vehicles[3] =
{
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
};

void addCity()
{
    if(cityCount >= MAX_CITIES)
    {
        printf("City limit reached\n");
        return;
    }

    printf("Enter city name: ");
    scanf("%s", cities[cityCount].name);
    cityCount++;
    printf("City '%s' added successfully!\n", cities[cityCount-1].name);
}

void displayCities()
{
    printf("\n=== Available Cities ===\n");
    if(cityCount == 0)
    {
        printf("No cities added yet.\n");
        return;
    }

    for(int i = 0; i < cityCount; i++)
    {
        printf("%d. %s\n", i + 1, cities[i].name);
    }
}

void editDistance()
{
    int sourceIdx, destIdx, distance;

    if(cityCount < 2)
    {
        printf("Need at least 2 cities to set distances!\n");
        return;
    }

    displayCities();
    printf("Enter source city number: ");
    scanf("%d", &sourceIdx);
    printf("Enter destination city number: ");
    scanf("%d", &destIdx);

    if(sourceIdx < 1 || sourceIdx > cityCount || destIdx < 1 || destIdx > cityCount)
    {
        printf("Invalid city selection!\n");
        return;
    }

    if(sourceIdx == destIdx)
    {
        printf("Distance from a city to itself is always 0.\n");
        return;
    }

    printf("Enter distance in kilometers: ");
    scanf("%d", &distance);

    // Set distance both ways (symmetric)
    distanceMatrix[sourceIdx-1][destIdx-1] = distance;
    distanceMatrix[destIdx-1][sourceIdx-1] = distance;

    printf("Distance between %s and %s set to %d km\n",
           cities[sourceIdx-1].name, cities[destIdx-1].name, distance);
}


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

