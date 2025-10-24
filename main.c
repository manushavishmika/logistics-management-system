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




void displayDistanceTable()
{
    if(cityCount == 0)
    {
        printf("No cities to display!\n");
        return;
    }

    printf("\n=== Distance Matrix (km) ===\n");

    // Header row
    printf("%-12s", "");
    for(int i = 0; i < cityCount; i++)
    {
        printf("%10s", cities[i].name);
    }
    printf("\n");

    // Data rows
    for(int i = 0; i < cityCount; i++)
    {
        printf("%-12s", cities[i].name);
        for(int j = 0; j < cityCount; j++)
        {
            if(i == j)
            {
                printf("%10d", 0);
            }
            else
            {
                printf("%10d", distanceMatrix[i][j]);
            }
        }
        printf("\n");
    }
}




void addDelivery()
{
    if(deliveryCount >= MAX_DELIVERIES)
    {
        printf("Cannot add more deliveries , limit reached\n");
        return;
    }

    if(cityCount < 2)
    {
        printf("Need at least 2 cities for delivery\n");
        return;
    }


    displayCities();

    Delivery newDelivery;

    printf("Enter source city number: ");
    scanf("%d", &newDelivery.source);
    printf("Enter destination city number: ");
    scanf("%d", &newDelivery.destination);


    if(newDelivery.source < 1 || newDelivery.source > cityCount ||
            newDelivery.destination < 1 || newDelivery.destination > cityCount)
    {
        printf("Invalid city selection!\n");
        return;
    }


    if(newDelivery.source == newDelivery.destination)
    {
        printf("Source and destination cannot be the same city.\n");
        return;
    }


    printf("Enter package weight (kg): ");
    scanf("%f", &newDelivery.weight);

    printf("\nAvailable vehicles:\n");
    printf("1. Van (up to %d kg)\n", vehicles[0].capacity);
    printf("2. Truck (up to %d kg)\n", vehicles[1].capacity);
    printf("3. Lorry (up to %d kg)\n", vehicles[2].capacity);
    printf("Select vehicle type: ");
    scanf("%d", &newDelivery.vehicleType);


    if(newDelivery.vehicleType < 1 || newDelivery.vehicleType > 3)
    {
        printf("Invalid vehicle selection!\n");
        return;
    }

    Vehicle selectedVehicle = vehicles[newDelivery.vehicleType - 1];


    // Check capacity
    if(newDelivery.weight > selectedVehicle.capacity)
    {
        printf("Package too heavy for %s! Maximum capacity: %d kg\n",
               selectedVehicle.name, selectedVehicle.capacity);
        return;
    }


    // Get distance between cities
    newDelivery.distance = distanceMatrix[newDelivery.source - 1][newDelivery.destination - 1];

    if(newDelivery.distance == 0)
    {
        printf("Distance not set between these cities! Please set distance first.\n");
        return;
    }


    // Calculate all the costs - this could probably be moved to a separate function
    newDelivery.cost = newDelivery.distance * selectedVehicle.rate * (1 + newDelivery.weight / 10000.0);
    newDelivery.fuelUsed = newDelivery.distance / selectedVehicle.efficiency;
    newDelivery.fuelCost = newDelivery.fuelUsed * FUEL_PRICE;
    newDelivery.totalCost = newDelivery.cost + newDelivery.fuelCost;
    newDelivery.profit = newDelivery.cost * 0.25;  // 25% profit margin
    newDelivery.customerCharge = newDelivery.totalCost + newDelivery.profit;
    newDelivery.time = newDelivery.distance / selectedVehicle.speed;


    // Store the delivery
    deliveries[deliveryCount] = newDelivery;
    deliveryCount++;


    // Show results to user
    printf("\n=== Delivery Details ===\n");
    printf("Route: %s -> %s\n",
           cities[newDelivery.source - 1].name,
           cities[newDelivery.destination - 1].name);
    printf("Vehicle: %s\n", selectedVehicle.name);
    printf("Distance: %.1f km\n", newDelivery.distance);
    printf("Estimated time: %.2f hours\n", newDelivery.time);
    printf("Customer charge: LKR %.2f\n", newDelivery.customerCharge);
    printf("Delivery added successfully!\n");
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




int main()
{
    for(int i = 0; i < MAX_CITIES; i++)
    {
        for(int j = 0; j < MAX_CITIES; j++)
        {
            distanceMatrix[i][j] = 0;
        }
    }

    showMainMenu();



    return 0;
}
