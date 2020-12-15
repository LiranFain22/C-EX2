//
// Created by Liran on 12/12/2020.
//

#ifndef EXERCISE2_AIRPORTENTITIES_H
#define EXERCISE2_AIRPORTENTITIES_H
#define STRING_MAX_SIZE 255

struct Airport {
    char *airportName;
    char *countryName;
    char *IATA;

    int (*airportIdentical)(struct Airport *airport1, struct Airport *airport2);
    int (*IATAIdentical)(struct Airport *airport, char *IATA);

    void (*inputAirportName)();
    void (*printAirport)(struct Airport *airport);
    void (*freeAirport)(struct Airport *airport);
};

struct AirportManager {
    char *airportManagerName;
    struct Airport *airports;
    int airportsSize;

    void (*addAirport)(struct AirportManager *manager, struct Airport airport);
    struct Airport *(*findAirportByIATA)(struct AirportManager *manager, char *IATA);

    void (*printAirportManager)();
    void (*freeAirportManager)();
};

struct Date{
    int day;
    int month;
    int year;

    int (*checkDate)(int dd, int mm, int yyyy);
    void (*getDepartureDateFromUser)(struct Date *date);
};

struct Flight{
    char *IATATakeoff;
    char *IATALanding;
    int takeoffTime;
    struct Date *date;

    int (*checkReceiveFlightDestination)(struct Flight *flight, char *takeoffIATA, char *landingIATA);
    int (*checkFlightsLineCount)(struct Flight *flights, char *takeoffIATA, char *landingIATA);

    void (*userInput)();
    void (*printFlight)();
    void (*freeFlight)();
};

struct Airline{
    char *companyName;
    int flightsCounter;
    struct Flight *airlineFlights;


    void (*addFlight)(struct Flight *airLineFlights, struct Flight flight);
    void (*printAirlineFlightsLine)(char *takeoffIATA, char *landingIATA);

    void (*userInput)();
    void (*printAirline)();
    void (*freeAirline)();
};


#endif //EXERCISE2_AIRPORTENTITIES_H
