#include <stdio.h>
#include <stdlib.h>
#include "airportEntities.h"


void menu(){

}

int main() {
/////////////////////////////////////////////////////////////////////
    // TODO - maybe need to put in function like 'initAirport'
    int airportsSize = 0;
    printf("Please Enter Number of Airports:");
    scanf("%d",&airportsSize);

    struct Airport *airports;
    airports = malloc(airportsSize * sizeof(struct Airport));
    if(!airports){
        printf("ERROR! Out of memory!\n");
        return 1;
    }
    printf("Please Enter Airport Manager Name:");
    char airportManagerName[STRING_MAX_SIZE];
    scanf("%s",airportManagerName);

    struct AirportManager *airportManager;
    airportManager = malloc(1 * sizeof(struct AirportManager));
    if(!airportManager){
        printf("ERROR! Out of memory!\n");
        return 1;
    }
    airportManager->airportManagerName = airportManagerName;
    airportManager->airports = airports;
    airportManager->airportsSize = airportsSize;
/////////////////////////////////////////////////////////////////////

    menu();

    return 0;
}
