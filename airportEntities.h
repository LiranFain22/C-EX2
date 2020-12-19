#ifndef EXERCISE2_AIRPORTENTITIES_H
#define EXERCISE2_AIRPORTENTITIES_H
#define STRING_MAX_SIZE 255

struct Airport {
    char *airportName;
    char *countryName;
    char *IATA;
};

struct AirportManager {
    struct Airport *airports;
    int airportsSize;
};

struct Date{
    int day;
    int month;
    int year;
};

struct Flight{
    char *IATATakeoff;
    char *IATALanding;
    int takeoffTime;
    struct Date *date;
};

struct Airline{
    char *companyName;
    int flightsCounter;
    struct Flight *airlineFlights;
};

//////////////////////--Airport methods--//////////////////////
int airportIdentical(struct Airport *airport1, struct Airport *airport2);
int IATAIdentical(struct Airport *airport, const char *IATA);
void userInput(struct Airport *airports, int airportsSize,
               char *airportName, char *countryName, char *IATA);
void printAirport(struct Airport *airport);
void freeAirport(struct Airport *airport);
///////////////////////////////////////////////////////////////

//////////////////////--AirportManager methods--//////////////////////
void addAirport(struct AirportManager *manager);
struct Airport *findAirportByIATA(struct AirportManager *manager, char *IATA);
void printAirportManager(struct AirportManager *manager);
void freeAirportManager(struct AirportManager *manager);
//////////////////////////////////////////////////////////////////////

//////////////////////--Flight methods--//////////////////////
int checkReceiveFlightDestination(struct Flight *flight, char *takeoffIATA, char *landingIATA);
int checkFlightsLineCount(struct Airline *airline, char *takeoffIATA, char *landingIATA);
void printFlight(struct Flight *flight);
void freeFlight(struct Flight *flight);
//////////////////////////////////////////////////////////////

//////////////////////--Airline methods--//////////////////////
void addFlight(struct AirportManager *manager, struct Airline *airline);
void printAirlineFlightsLine(struct Airline *airline);
void airlineUserInput(char *airlineName);
void printAirline(struct Airline *airline);
void freeAirline(struct Airline* airline);
///////////////////////////////////////////////////////////////

//////////////////////--Date methods--//////////////////////
int checkDate(char* dateStr, int dd, int mm, int yyyy);
void getDepartureDateFromUser(struct Date *date);
////////////////////////////////////////////////////////////

#endif //EXERCISE2_AIRPORTENTITIES_H
