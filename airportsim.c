#include "airportsim.h"



/* Start: print messages and initialize the parameters.
    Pre: None.
    Post: Asks user for responses and initializes all variables specified as parameters.
    Uses: UserSaysYes. */
void Start(int *endtime, double *expectarrive, double *expectdepart) {
    int ok;
    printf("This program simulates an airport with only one runway.\n"
           "One plane can land or depart in each unit of time.\n"
           "Up to %d planes can be waiting to land or take off "
           "at any time.\n", MAXQUEUE);
    printf("How many units of time will the simulation run? ");
    scanf("%d", endtime);
    Randomize();
    do {
        printf("Expected number of arrivals per unit time "
                "(real number)? ");
        scanf("%lf", expectarrive);
        printf("Expected number of departures per unit time? ");
        scanf("%lf", expectdepart);
        if (*expectarrive < 0.0 || *expectdepart < 0.0) {
            printf("These numbers must be nonnegative.\n");
            ok = 0;
        } else if (*expectarrive + *expectdepart > 1.0) {
            printf("The airport will become saturated. "
                   "Read new numbers? ");
            ok = !UserSaysYes(); /* If user says yes, repeat loop. */
        } else
            ok = 1;
    } while (ok == 0);
}

/* NewPlane: make a new record fora plane, update nplanes.
    Pre: None.
    Post: Makes a new structure for a plane and updates nplanes. */
void NewPlane(Plane *p, int *nplanes, int curtime, Action kind) {
    (*nplanes)++;
    p->id = *nplanes;
    p->tm = curtime;
    switch(kind) {
        case ARRIVE:
            printf("Plane %3d ready to land.\n", *nplanes);
            break;
        case DEPART:
            printf("Plane %3d ready to take off.\n", *nplanes);
            break;
    }
}

/* Refuse'processes a plane when the queue is full.
    Pre: None.
    Post: Processes a plane wanting to use runway, but the queue is full. */
void Refuse(Plane p, int *nrefuse, Action kind) {
    switch(kind) {
        case ARRIVE:
            printf("Plane %3d directed to another airport.\n", p.id);
            break;
        case DEPART:
            printf("Plane %3d told to try later.\n", p.id);
            break;
    }
    (*nrefuse)++;
}

/* Land: process a plane that is actually landing.
    Pre: None.
    Post: Processes a plane p that is actually landing. */
void Land(Plane p, int curtime, int *nland, int *landwait) {
    int wait;
    wait = curtime - p.tm;
    printf("%3d : Plane %3d landed; in queue %d units.\n", curtime, p.id, wait);
    (*nland)++;
    *landwait += wait;
}

/* Fly: process a plane that is actually taking off.
    Pre: None.
    Post: Processes a plane p that is actually taking off. */
void Fly(Plane p, int curtime, int *ntakeoff, int *takeoffwait) {
    int wait;
    wait = curtime - p.tm;
    printf("%3d : Plane %3d took off; in queue %d units.\n",
           curtime, p.id, wait);
    (*ntakeoff)++;
    *takeoffwait += wait;
}

/* Idle: updates variables for idle runway.
    Pre: None.
    Post: Updates variables for a time unit when the runway is idle. */
void ldle(int curtime, int *idletime) {
    printf("%3d : Runway is idle.\n", curtime);
    (*idletime)++;
}

/* Conclude: write out statistics and conclude simulation.
    Pre: None.
    Post: Writes out all the statistics and concludes the simulation. */
void Conclude(int nplanes, int nland, int ntakeoff,
              int nrefuse, int landwait, int takeoffwait,
              int idletime, int endtime,
              Queue *pt, Queue *pl) {
    printf("Simulation has concluded after %d units.\n", endtime);
    printf("Total number of planes processed: %3d\n", nplanes);
    printf(" Number of planes landed: %3d\n", nland);
    printf("Number of planes taken off: %3d\n", ntakeoff);
    printf(" Number of planes refused use: %3d\n", nrefuse);
    printf(" Number left ready to land: %3d\n", QueueSize(pl));
    printf(" Number left ready to take off: %3d\n", QueueSize(pt));

    if (endtime > 0)
        printf(" Percentage of time runway idle: %6.2f\n", ((double) idletime/endtime) * 100.0);
    if (nland > 0)
        printf(" Average wait time to land: %6.2f\n", (double) landwait/nland);
    if (ntakeoff > 0)
        printf(" Average wait time to take off: %6.2f\n", (double) takeoffwait/ntakeoff);
}

/* Randomize: set starting point for pseudorandom integers. */
void Randomize(void) {
    srand((unsigned int) (time(NULL) % 10000));
}

/* PoissonRandom: generate a pseudorandom integer according to the Poisson distribution.
    Pre: None.
    Post: Generates a random nonnegative integer according to a Poisson distribution
    with the expected value given as the parameter.
    Uses: exp, rand. */
int PoissonRandom(double expectedvalue) {
    int n = 0; /* counter of iterations */
    double limit; /* e^-v, where v is the expected value */
    double x; /* pseudorandom number */
    limit = exp(-expectedvalue);
    x = rand() / (double) INT_MAX;
    while (x > limit) {
        n++;
        x *= rand() / (double) INT_MAX;
    }
    return n;
}

int UserSaysYes() {
    int ok;
    scanf("%d", &ok);
    return ok;
}