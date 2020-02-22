#include "controller.h"
#include "ordre.h"
#include "hardware.h"


int volatile queue_up[HARDWARE_NUMBER_OF_FLOORS - 1] = {0,0,0}; //Sorter liste for hver gang det kommer en ny bestilling.
int volatile queue_inside[HARDWARE_NUMBER_OF_FLOORS] = {0,0,0,0};
int volatile queue_down[HARDWARE_NUMBER_OF_FLOORS - 1] = {0,0,0};//Sorter hver gang det kommer en ny bestilling.


void sort_queue(int up_down){
    if(up_down){

    }
    else{

    }
}
