#include "hardware.h"
#include "ordre.h"
#include <stdio.h>


#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static int last_floor = BETWEEN_FLOORS;
static HardwareMovement current_movement = HARDWARE_MOVEMENT_STOP;
static HardwareMovement last_movement = HARDWARE_MOVEMENT_STOP;
static HardwareMovement movement_before_stop = HARDWARE_MOVEMENT_STOP;


void initialize(){

}

void idle(action action){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
}

void go_up(action action){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
}

void go_down(action action){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
}

void halt(action action){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
    }

}





int get_current_floor(){
    return current_floor;
}






//Controlleren må være "føleren" som skal kjenne på sensorene til en hver tid.
//Må ta i bruk ordre for å heise heisen i den retningen som er ønskelig.

//Trenger å initialize


//Polle etter
