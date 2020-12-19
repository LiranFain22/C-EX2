#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "airportEntities.h"

int IATAValid(struct AirportManager *manager, char *iata);
int upperFirstLetter(const char *token, char *correctedAirportName, int currentIndex);
int lowerFirstLetter(const char *token, char *correctedAirportName, int currentIndex);

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
void addAirport(struct AirportManager *manager){
    char airportName[STRING_MAX_SIZE],airportCountry[STRING_MAX_SIZE],IATA[STRING_MAX_SIZE];

    userInput(manager->airports, manager->airportsSize,airportName,airportCountry,IATA);

    if(manager->airportsSize == 0){
        manager->airports = (struct Airport *) malloc(sizeof (struct Airport));
    } else {
        manager->airports = realloc(manager->airports, (manager->airportsSize + 1) * sizeof(struct Airport));
    }
    if(manager->airports == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    manager->airports[manager->airportsSize].airportName = (char *) malloc(strlen(airportName)+1);
    if(! manager->airports[manager->airportsSize].airportName){
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(manager->airports[manager->airportsSize].airportName,airportName);

    manager->airports[manager->airportsSize].countryName = (char *) malloc(strlen(airportCountry)+1);
    if(! manager->airports[manager->airportsSize].countryName){
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(manager->airports[manager->airportsSize].countryName,airportCountry);

    manager->airports[manager->airportsSize].IATA = (char *) malloc(4);
    if(! manager->airports[manager->airportsSize].IATA){
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(manager->airports[manager->airportsSize].IATA,IATA);

    printf("\nAirport Added Successfully\n\n");
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

/**
 * This method get airline, IATA source code and IATA destination code and return number of flights that
 * airline have in this destinations.
 * @param airline that checked on
 * @param takeoffIATA IATA source code that given
 * @param landingIATA IATA destination code that given
 * @return number of flights
 */
int checkFlightsLineCount(struct Airline *airline, char *takeoffIATA, char *landingIATA){
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
void addFlight(struct AirportManager *manager, struct Airline *airline){
    char IATATakeoff[STRING_MAX_SIZE],IATALanding[STRING_MAX_SIZE],takeoffTime[STRING_MAX_SIZE];
    if(airline->flightsCounter == 0){
        airline->airlineFlights = malloc(sizeof(struct Flight));
    } else {
        airline->airlineFlights = realloc(airline->airlineFlights, (airline->flightsCounter + 1) * sizeof(struct Flight));
    }
    if(airline->airlineFlights == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Please Enter IATA source code: ");
    gets(IATATakeoff);
    while(! IATAValid(manager,IATATakeoff)){
        printf("IATA Invalid, please try again\n\n");
        printf("Please Enter IATA source code: ");
        gets(IATATakeoff);
    }
    printf("\nPlease Enter IATA destination code: ");
    gets(IATALanding);
    while(! IATAValid(manager,IATALanding) || strcmp(IATATakeoff,IATALanding)==0){
        printf("IATA Invalid, please try again\n\n");
        printf("Please Enter IATA destination code: ");
        gets(IATALanding);
    }

    printf("\nPlease Enter Takeoff Time: ");
    gets(takeoffTime);
    int time = strtol(takeoffTime,NULL,10);
    while (!isdigit(takeoffTime[0])  || !isdigit(takeoffTime[1]) || time>23 || time<0){
        printf("invalid takeoff time, please try again\n");
        printf("\nPlease Enter Takeoff Time: ");
        gets(takeoffTime);
        time = strtol(takeoffTime,NULL,10);
    }

    airline->airlineFlights[airline->flightsCounter].IATATakeoff = (char *)malloc(4);
    strcpy(airline->airlineFlights[airline->flightsCounter].IATATakeoff,IATATakeoff);

    airline->airlineFlights[airline->flightsCounter].IATALanding = (char *)malloc(4);
    strcpy(airline->airlineFlights[airline->flightsCounter].IATALanding,IATALanding);
    airline->airlineFlights[airline->flightsCounter].date = (struct Date *) malloc(sizeof(struct Date));
    getDepartureDateFromUser(airline->airlineFlights[airline->flightsCounter].date);

    airline->airlineFlights[airline->flightsCounter].takeoffTime = time;

    airline->flightsCounter += 1;
}

/**
 * This method print a count of airline's flights
 * @param airline that checked on
 * @param takeoffIATA code for check
 * @param landingIATA code for check
 */
void printAirlineFlightsLine(struct Airline *airline){
    char takeoffIATA[STRING_MAX_SIZE], landingIATA[STRING_MAX_SIZE];

    printf("Please Enter IATA Source Code: ");
    gets(takeoffIATA);
    while (!IATAValid(NULL,takeoffIATA)){
        printf("IATA Invalid, please try again\n");
        printf("Please Enter IATA Source Code: ");
        gets(takeoffIATA);
    }

    printf("\nPlease Enter IATA Destination Code: ");
    gets(landingIATA);
    while (!IATAValid(NULL,landingIATA)){
        printf("IATA Invalid, please try again\n");
        printf("Please Enter IATA Destination Code: ");
        gets(landingIATA);
    }

    int flightsCounter = checkFlightsLineCount(airline,takeoffIATA,landingIATA);
    printf("\nThis Airline Have %d flights in this line\n\n", flightsCounter);
}

/**
 * This method correct airport name by the condition of the exercise
 * @param airportName that given to method
 * @return new airport name by the condition of the exercise
 */
int fixAirportName(char *airportName) {
     char *space = " ";
     char *token = NULL;
     char correctedAirportName[STRING_MAX_SIZE];
     int firstWord = 1;
     int currentIndex = 0;

     token = strtok(airportName, space);
     if(token == NULL){
         printf("Invalid airport name, please try again\n");
         return 0;
     }
     char *nextToken = strtok(NULL, space);
     while (nextToken != NULL || firstWord == 1) {
         firstWord = 0;
         if (strlen(token) > 0) {
             if (strlen(token) % 2 == 0) {
                 int i;
                 for (i = 0; i < strlen(token); i++) {
                     if (i % 2 == 0) {
                         correctedAirportName[currentIndex] = toupper(token[i]);
                     } else {
                         correctedAirportName[currentIndex] = tolower(token[i]);
                     }
                     currentIndex++;
                 }
                 correctedAirportName[currentIndex++] = ' ';
                 correctedAirportName[currentIndex++] = ' ';

             } else {
                 currentIndex = upperFirstLetter(token, correctedAirportName, currentIndex);
             }
         }
         token = nextToken;
         nextToken = strtok(NULL, space);
     }


     if (token != NULL) {
         if(strlen(token)%2 == 0){
             int i;
             for (i = 0; i < strlen(token); i++) {
                 if (i % 2 == 0) {
                     correctedAirportName[currentIndex] = toupper(token[i]);
                 } else {
                     correctedAirportName[currentIndex] = tolower(token[i]);
                 }
                 currentIndex++;
             }
             correctedAirportName[currentIndex] = '\0';
         } else{
             currentIndex = lowerFirstLetter(token, correctedAirportName, currentIndex);
             correctedAirportName[currentIndex-2] = '\0';
         }
         //to lower token's first letter
     } else {
         correctedAirportName[currentIndex-2] = '\0';
     }
     strcpy(airportName, correctedAirportName); //suppose override the airport name
     return 1;
 }

 /**
  * This method make the current letter in the sentence to be capital letter and
  * fill the other letters in corrected airport name.
  * @param token the word to be changed
  * @param correctedAirportName string to be changed
  * @param currentIndex index where letter to be changed
  * @return index to next letter in sentence
  */
int upperFirstLetter(const char *token, char *correctedAirportName, int currentIndex) {
    int j;
    for(j = 0; j < strlen(token); j++){
        if(j == 0){
            correctedAirportName[currentIndex] = toupper(token[j]);
        }else{
            correctedAirportName[currentIndex] = token[j];
        }
        currentIndex++;
    }
    correctedAirportName[currentIndex++] = ' ';
    correctedAirportName[currentIndex++] = ' ';
    return currentIndex;
}

/**
 * This method make the current letter in the sentence to be lower-case letter and
 * fill the other letters in corrected airport name.
 * @param token the word to be changed
  * @param correctedAirportName string to be changed
  * @param currentIndex index where letter to be changed
  * @return index to next letter in sentence
 */
int lowerFirstLetter(const char *token, char *correctedAirportName, int currentIndex) {
    int j;
    for(j = 0; j < strlen(token); j++){
        if(j == 0){
            correctedAirportName[currentIndex] = tolower(token[j]);
        }else{
            correctedAirportName[currentIndex] = token[j];
        }
        currentIndex++;
    }
    correctedAirportName[currentIndex++] = ' ';
    correctedAirportName[currentIndex++] = ' ';
    return currentIndex;
}

/**
 * This method get input by user for airport name and make airport name by the condition of the exercise
 */
void inputAirportName(char * airportName){
    printf("Please Enter Airport name: ");
    gets(airportName);
    while(fixAirportName(airportName) == 0){
        inputAirportName(airportName);
    }
}

/**
 * This method get input by user for airport country
 * @param countryName string name to be given
 */
void inputAirportCountry(char *countryName){
    printf("Please Enter Airport country: ");
    gets(countryName);
}

/**
 * This method get input by user for IATA code
 * @param airports to be checked if the code already exist
 * @param airportsSize - number if airport to be checked in
 * @param IATA code given by user
 */
void inputAirportIATA(struct Airport *airports, int airportsSize, char *IATA){
    printf("Please Enter Airport IATA code: ");
    gets(IATA);
    if(IATAValid(NULL,IATA)){
        for(int i=0; i< airportsSize; i++){
            if(IATAIdentical(&airports[i],IATA)){
                printf("IATA already exist, please try again\n");
                inputAirportIATA(airports,airportsSize,IATA);
                return;
            }
        }
    } else {
        printf("IATA Invalid, please try again\n");
        inputAirportIATA(airports,airportsSize, IATA);
    }

}

/**
 * This method check if IATA code is valid
 * @param manager - airport manager to be checked in
 * @param IATA  - code to be checked
 * @return 1 - is IATA code is valid, 0 - invalid
 */
int IATAValid(struct AirportManager*manager,char *IATA) {
    int IATASize = strlen(IATA);
    if(IATASize == 3){
        int i;
        for(i = 0; i < IATASize; i++){
            char ch = IATA[i];
            if(ch < 'A' || ch > 'Z')
                return 0;
        }
        if(manager!= NULL && !findAirportByIATA(manager,IATA)){
            return 0;
        }
        return 1;
    }
    return 0;
}

/**
 * This method get input by user
 * @param airports to be checked on
 * @param airportsSize - number of airports
 * @param airportName  - airport name input by user
 * @param countryName  - country name input by user
 * @param IATA - IATA code input by user
 */
void userInput(struct Airport *airports, int airportsSize, char *airportName, char *countryName, char *IATA){
    inputAirportName(airportName);
    inputAirportCountry(countryName);
    inputAirportIATA(airports,airportsSize,IATA);
}

/**
 * This method check if the date is valid
 * @param dd int day that given
 * @param mm int month that given
 * @param yyyy int year that given
 * @return 1 - if date is valid, otherwise 0 - (invalid date)
 */
int checkDate(char* dateStr,int dd,int mm,int yyyy){
    if(strlen(dateStr) == 10 && dateStr[2] =='/' && dateStr[5] == '/') {
        //check year
        if (yyyy >= 1900 && yyyy <= 9999) {
            //check month
            if (mm >= 1 && mm <= 12) {
                //check day
                if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8))
                    return 1;
                else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                    return 1;
                else if ((dd >= 1 && dd <= 28) && (mm == 2))
                    return 1;
            } else
                return 0; // Month invalid
        } else
            return 0; // Year invalid
        return 1; // Date valid
    } else{
        return 0;
    }
}
/**
 * This method get departure date from user
 * @param date that given by user
 */
void getDepartureDateFromUser(struct Date *date){

    printf("Please Enter Departure Date (format - DD/MM/YYYY) : ");
    int dd = -1,mm = -1,yyyy = -1;
    char dateStr[STRING_MAX_SIZE];

    gets(dateStr);
    sscanf(dateStr,"%d/%d/%4d",&dd,&mm,&yyyy);
    if(dd == -1 || mm == -1 || yyyy == -1){
        printf("Invalid date\n");
    }
     if(checkDate(dateStr,dd,mm,yyyy) == 0){
         printf("Invalid date\n");
         getDepartureDateFromUser(date);
         return;
     }
     date->day = dd;
     date->month = mm;
     date->year = yyyy;
}

/**
 * This method get input by user for airline name
 * @param airlineName input by user
 */
void airlineUserInput(char *airlineName){
    printf("Please Enter Airline Name: ");
    gets(airlineName);
    printf("\n");
}

/**
 * This method free flight memory
 * @param flight to be freed
 */
void freeFlight(struct Flight *flight){
    free(flight->IATALanding);
    free(flight->IATATakeoff);
    free(flight->date);
}

/**
 * This method free airline memory
 * @param airline to be freed
 */
void freeAirline(struct Airline* airline) {
    int i;
    for (i=0; i<airline->flightsCounter ; i++) {
        freeFlight(&airline->airlineFlights[i]);
    }
    free(airline->airlineFlights);
    free(airline);
}

/**
 * This method free airport manager memory
 * @param manager to be freed
 */
void freeAirportManager(struct AirportManager *manager){
    int i;
    for(i=0; i<manager->airportsSize; i++){
        freeAirport(&manager->airports[i]);
    }
    free(manager->airports);
    free(manager);
}

/**
 * This method free airport memory
 * @param airport to be freed
 */
void freeAirport(struct Airport *airport){
    free(airport->airportName);
    free(airport->countryName);
    free(airport->IATA);
}

/**
 * This method print airport details
 * @param airport to be printed
 */
void printAirport(struct Airport *airport){
    printf("--------------------------------------------\n");
    printf("Airport Name: %s\n", airport->airportName);
    printf("Airport County: %s\n", airport->countryName);
    printf("Airport IATA Code: %s\n", airport->IATA);
    printf("--------------------------------------------\n");
}

/**
 * This method print airline details
 * @param airline to be printed
 */
void printAirline(struct Airline *airline){
    printf("--------------------------------------------\n");
    printf("Airline Name: %s\n", airline->companyName);
    printf("Airline flights number: %d\n", airline->flightsCounter);
    int i;
    for(i = 0; i < airline->flightsCounter; i++){
        printFlight(&airline->airlineFlights[i]);
    }
    printf("--------------------------------------------\n");
};

/**
 * This method print airport manage details
 * @param manager to be printed
 */
void printAirportManager(struct AirportManager* manager){
    printf("============================================\n");
    printf("All Airports in Airport Manager: \n");
    int i;
    for(i = 0; i < manager->airportsSize; i++){
        printAirport(&manager->airports[i]);
    }
    printf("============================================\n");

}

/**
 * This method print flight details
 * @param flight to be printed
 */
void printFlight(struct Flight *flight){
    printf("--------------------------------------------\n");
    printf("IATA Source Code: %s\n", flight->IATATakeoff);
    printf("Airline Destination Code: %s\n", flight->IATALanding);
    printf("Takeoff Time: %d\n", flight->takeoffTime);
    printf("%d/%d/%d\n",flight->date->day,flight->date->month,flight->date->year);
    printf("--------------------------------------------\n");
}


