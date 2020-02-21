#include "controller.h"
#include "ordre.h"


int volatile queue_up[3] = {0,0,0}; //Sorter liste for hver gang det kommer en ny bestilling.
int volatile queue_inside[4] = {0,0,0,0};
int volatile queue_down[3] = {0,0,0};//Sorter hver gang det kommer en ny bestilling.
