#include "controller.h"
#include "ordre.h"




struct queue{
    int volatile queue_up[get_number_of_floors() - 1] = {0,0,0}; //Sorter liste for hver gang det kommer en ny bestilling.
    int volatile queue_inside[get_number_of_floors()] = {0,0,0,0};
    int volatile queue_down[get_number_of_floors() - 1] = {0,0,0};//Sorter hver gang det kommer en ny bestilling.
};


void sort_queue(int up_down){
    if(up_down){

    }
    else{

    }
}

void dequeue(struct queue *queue){

}
