#include "hardware.h"
#include "ordre.h"
#include <stdio.h>


#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static HardwareMovement current_movement = HARDWARE_MOVEMENT_STOP;
static action action = ENTER;
static state state = IDLE;


void initialize(){

}



void idle(){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
        default:
        break;
}

void go_up(){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
        default:
        break;
}

void go_down(){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
        default:
        break;
}

void halt(){
    switch (action) {
        case ENTER:
            break;
        case INSIDE:
            break;
        case EXIT:
            break;
        default:
        break;

    }

}


void next_state(state next_state, action next_action){
        state = next_state;
        action = next_action;
}

state get_next_state(){
    return state;
}


int get_current_floor(){
    return current_floor;
}






//Controlleren må være "føleren" som skal kjenne på sensorene til en hver tid.
//Må ta i bruk ordre for å heise heisen i den retningen som er ønskelig.

//Trenger å initialize


//Polle etter
