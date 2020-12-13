//
// Created by Liran on 12/12/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "airportEntities.h"

/**
 * This method get 2 airports and return:
 * 1 - if airports are equal by IATA code
 * 0 - otherwise.
 * @param airport1 first airport to be checked
 * @param airport2 second airport to be checked
 * @return 1 - airports are equals, 0 - otherwise
 */
int airportIdentical(struct Airport *airport1, struct Airport *airport2){
    if(strcmp(airport1->IATA,airport2->IATA) == 0)
        return 1;
    return 0;
}

/**
 * This method get airport and IATA code and return:
 * 1 - if airport's IATA code is equal to IATA given
 * 0 - otherwise.
 * @param airport's IATA to be checked
 * @param IATA given to compare to
 * @return 1 - IATA codes are equal, 0 - otherwise
 */
int IATAIdentical(struct Airport *airport, const char *IATA){
    if(strcmp(airport->IATA,IATA) == 0)
        return 1;
    return 0;
}

/**
 * This method add airport to array of airports
 * @param airports array
 * @param airportSize size of airports array
 * @param airport to be added
 */
void addAirport(struct AirportManager *manager, struct Airport airport){
    //TODO should init size and airports
    manager->airports = realloc(manager->airports, (manager->airportsSize + 1) * sizeof(airport));

    if(manager->airports == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    manager->airports[manager->airportsSize] = airport;
    manager->airportsSize += 1;
}

/**
 * This method finds airport by IATA code
 * @param manager the airportManager to be searched
 * @param IATA code to be found in airports array
 * @return airport's pointer with the same IATA code
 */
struct Airport *findAirportByIATA(struct AirportManager *manager, char *IATA){
    int i;
    for(i = 0; i < manager->airportsSize; i++){
        if(IATAIdentical(&manager->airports[i],IATA) == 1)
            return &manager->airports[i];
    }

    return NULL; // if there is not airport's code with the same IATA code that given
}

/**
 * This method get flight, takeoff code, landing code and verifies that takeoff and landing code's flight
 * are match to codes that given
 * @param flight that given for check
 * @param takeoffIATA code for verified with takeoff code's flight
 * @param landingIATA code for verified with landing code's flight
 * @return 1 - if codes are match,
 *         0 - otherwise
 */
int checkReceiveFlightDestination(struct Flight *flight, char *takeoffIATA, char *landingIATA){
    if(strcmp((const char *) flight->IATATakeoff, takeoffIATA) == 0
    && strcmp((const char *) flight->IATALanding, landingIATA) == 0)
        return 1;
    return 0;
}

int checkFlightsLineCount(struct Airline *airline, char *takeoffIATA, char *landingIATA){
    //TODO ask !!!!
    int i;
    int flightsCounter = 0;
    for(i = 0; i < airline->flightsCounter; i++){
        if(checkReceiveFlightDestination(&airline->airlineFlights[i], takeoffIATA, landingIATA) == 1)
            flightsCounter++;
    }
    return flightsCounter;
}

/**
 * * This method add flight to airline
 * @param airline that flight will be added
 * @param flight that added to airline
 */
void addFlight(struct Airline *airline, struct Flight flight){
    //TODO should init size and airports
    airline->airlineFlights = realloc(airline->airlineFlights, (airline->flightsCounter + 1) * sizeof(struct Flight));


    if(airline->airlineFlights == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    airline->airlineFlights[airline->flightsCounter] = flight;
    airline->flightsCounter += 1;
}

/**
 * This method print a count of airline's flights
 * @param airline that checked on
 * @param takeoffIATA code for check
 * @param landingIATA code for check
 */
void printAirlineFlightsLine(struct Airline *airline, char *takeoffIATA, char *landingIATA){
    int flightsCounter = airline->airlineFlights->checkFlightsLineCount(airline->airlineFlights,takeoffIATA,landingIATA);
    printf("This Airline Have %d flights in this line", flightsCounter);
}