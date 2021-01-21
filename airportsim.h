#ifndef AIRPORT_SIMULATION_AIRPORTSIM_H
#define AIRPORT_SIMULATION_AIRPORTSIM_H

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

typedef enum action { ARRIVE, DEPART } Action;
void Start(int *endtime, double *expectarrive, double *expectdepart);
void NewPlane(Plane *p, int *nplanes, int curtime, Action kind);
void Refuse(Plane p, int *nrefuse, Action kind);
void Land(Plane p, int curtime, int *nland, int *landwait);
void Fly(Plane p, int curtime, int *ntakeoff, int *takeoffwait);
void ldle(int curtime, int *idletime);
void Conclude(int nplanes, int nland, int ntakeoff,
              int nrefuse, int landwait, int takeoffwait,
              int idletime, int endtime,
              Queue *pt, Queue *pl);
void Randomize(void);
int PoissonRandom(double expectedvalue);
int UserSaysYes();
#endif
