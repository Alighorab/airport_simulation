#include "queue.h"
#include "airportsim.h"

/* simulation of an airport */


int main(void) {
    Queue landing, takeoff;
    Queue *pl = &landing;
    Queue *pt = &takeoff;
    Plane plane;
    int curtime; /* current time; one unit = time for take off or landing */
    int endtime; /* total number of time units to run */
    double expectarrive; /* number of planes arriving in one unit */
    double expectdepart; /* number of planes newly ready to take off */
    int i; /* loop control variable */
    int idletime; /* number of units when runway is idle */
    int landwait; /* total waiting time for planes landed */
    int nland; /* number of planes landed */
    int nplanes; /* number of planes processed so far */
    int nrefuse; /* number of planes refused use of airport */
    int ntakeoff;/* number of planes taken off */
    int pri; /* pseudo-random integer */
    int takeoffwait; /* total waiting time for take off */

    CreateQueue(pl);
    CreateQueue(pt);
    nplanes = nland = ntakeoff = nrefuse = 0;
    landwait = takeoffwait = idletime = 0;
    Start(&endtime, &expectarrive, &expectdepart);
    for (curtime = 1; curtime <= endtime; curtime++) {
        pri = PoissonRandom(expectarrive);
        for (i = 1; i <= pri; i++) { /* Add to landing queue. */
            NewPlane( &plane, &nplanes, curtime, ARRIVE);
            if (QueueFull(pl))
                Refuse(plane, &nrefuse, ARRIVE);
            else
                Append(plane, pl);
        }
        pri = PoissonRandom(expectdepart);
        for (i = 1; i <= pri; i++) { /* Add to takeoff queue. */
            NewPlane(&plane, &nplanes, curtime, DEPART);
            if (QueueFull(pt))
                Refuse(plane, &nrefuse, DEPART);
            else
                Append(plane, pt);
        }
        /* Where you will use priority queue. */
        if (! QueueEmpty(pl)) { /* Bring plane to land. */
            Serve( &plane, pl);
            Land(plane, curtime, &nland, &landwait);
        } else if (!QueueEmpty(pt)) { /* Allow plane to take off. */
            Serve( &plane, pt);
            Fly(plane, curtime, &ntakeoff, &takeoffwait);
        } else
            ldle(curtime, &idletime);
        }
    Conclude(nplanes, nland, ntakeoff, nrefuse, landwait,
             takeoffwait, idletime, endtime, pt, pl);
    return 0;
}



