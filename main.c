#include <stdio.h>
#include <stdlib.h>
#include "airportEntities.h"


int menu(struct AirportManager *airportManager, struct Airline *airline){

    printf("Please Press Character For Proceed:\n"
           "A - adding flight to Airline\n"
           "B - adding airport to airports array\n"
           "C - printing Airline data\n"
           "D - printing Airport Manager data\n"
           "G - printing number of flight between 2 different airports\n"
           "E - exit program\n");

    char userInput;
    scanf("%c",&userInput);

    // TODO - continue here
    switch (userInput) {
        case 'A':{
            addFlight(airline);
            break;
        }
        case 'B':{
            addAirport(airportManager);
            break;
        }
        case 'C':{
            printAirline();//TODO lemashmesh !!
            break;
        }
        case 'D':{
            printAirportManager();//TODO lemashmesh
            break;
        }
        case 'G':{
            printAirlineFlightsLine(airline);
            break;
        }
        case 'E':{
            return 1;
        }
    }
    return 0;
}

int main() {

    // TODO - maybe need to put in function like 'initAirport'
    int airportsSize = 0;
    char airLineName[STRING_MAX_SIZE];
    int i;

    struct AirportManager *airportManager = (struct AirportManager *) malloc(sizeof(struct AirportManager));
    if(!airportManager){
        printf("ERROR! Out of memory!\n");
        return 1;
    }

    printf("Please Enter Number of Airports:");
    scanf("%d",&airportsSize);
    printf("\n\n");

    for (i = 0; i < airportsSize; ++i) {
        addAirport(airportManager);
    }

    struct Airline *airline = (struct Airline *) malloc(sizeof(struct Airline));
    if(!airline){
        printf("ERROR! Out of memory!\n");
        return 1;
    }

    airlineUserInput(airLineName);
    airline->flightsCounter = 0;
    int userContinue = menu(airportManager, airline);

    while(userContinue){
        userContinue = menu(airportManager, airline);
    };

    freeAirportManager(airportManager);
    freeAirline(airline);


    return 0;
}
