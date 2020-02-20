#include "controller.h"
#include "ordre.h"


int volatile queue_up[3] = {0,0,0}; //Sorter liste for hver gang det kommer en ny bestilling.
int volatile queue_inside[4] = {0,0,0,0};
int volatile queue_down[3] = {0,0,0};//Sorter hver gang det kommer en ny bestilling.

//Om den nye bestillingen er lavere enn dit du skal, stop og ta med,
//Samme motstatt for motsatt vei


//Sorter fra minst til størst, unntak er nullerne.



//Sorter fra størst til minst
