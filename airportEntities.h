//
// Created by Liran on 12/12/2020.
//

#ifndef EXERCISE2_AIRPORTENTITIES_H
#define EXERCISE2_AIRPORTENTITIES_H

struct Airport {
    char *airportName;
    char *countryName;
    char *IATA;

    int (*airportIdentical)(struct Airport *airport1, struct Airport *airport2);
    int (*IATAIdentical)(struct Airport *airport, char *IATA);

    void (*userInput)();
    void (*printAirport)();
    void (*freeAirport)();
};

struct AirportManager {
    struct Airport *airports;
    int airportsSize;

    void (*addAirport)(struct AirportManager *manager, struct Airport airport);
    struct Airport *(*findAirportByIATA)(struct AirportManager *manager, char *IATA);

    void (*userInput)();
    void (*printAirportManager)();
    void (*freeAirportManager)();
};

struct Date{
    int day;
    int month;
    int year;

    int (*checkDate)(struct Date *date);
};

struct Flight{
    struct Airport *takeoffAirport;
    struct Airport *landingAirport;
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


    void (*addFlight)(struct Flight *airLineFlights, struct Flight *flight);
    void (*printAirlineFlightsLine)(char *takeoffIATA, char *landingIATA);

    void (*userInput)();
    void (*printAirline)();
    void (*freeAirline)();
};


#endif //EXERCISE2_AIRPORTENTITIES_H
