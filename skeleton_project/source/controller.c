#include "hardware.h"
#include "ordre.h"
#include <stdio.h>


#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static HardwareMovement last_movement = HARDWARE_MOVEMENT_STOP;
static action action = ENTER;
static state state = IDLE;


void initialize(){


}



void idle(){
    if (any_requests()) {
        if (get_next_order < current_floor) {
            next_state(GOING_DOWN, ENTER)
        }
        else next_state(GOING_UP, ENTER)
    }

}

void go_up(){
    switch (action) {
        case ENTER:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        last_movement = HARDWARE_MOVEMENT_UP;
        next_state(GOING_UP, INSIDE);
            break;
        case INSIDE:
            for (int floor = current_floor; floor < get_next_order; floor++){
                if (check_floor_dir_value(floor, 0)){
                    put_order_on_hold(floor);
                }
            }
            if (current_floor == next_order) {
                next_state(HALT, ENTER);
            }
            break;
        default:
        break;
}

void go_down(){
    switch (action) {
        case ENTER:
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        last_movement = HARDWARE_MOVEMENT_DOWN;
        next_state(GOING_DOWN, INSIDE);
            break;
        case INSIDE:
        for (int floor = current_floor; floor > 0; floor--){
            if (check_floor_dir_value(floor, 1)){
                put_order_on_hold(floor);
            }
        }
        if (current_floor == next_order) {
            next_state(HALT, ENTER);
        }
            break;
        default:
        break;
}
}

void halt(){
    switch (action) {
        case ENTER:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        //OPEN DOOR for 3 seconds, Sette på en Timer.
        clear_floor_orders(current_floor);
        next_state(HALT, INSIDE);
            break;
        case INSIDE:
        //Hvis timeren er ferdig, hopp til exit, der vi lukker døren, og går videre.


            break;
        case EXIT:
        //Dørene lukkes.
        update_next_order();
        if (get_next_order == -1)) {
            next_state(IDLE, ENTER);
        }
        else if(get_next_order < current_floor){
            next_state(GOING_DOWN, ENTER);
        }
        else{
            next_state(GOING_UP, ENTER);
        }
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

void read_buttons(){
    get_button_signal();
}





//Controlleren må være "føleren" som skal kjenne på sensorene til en hver tid.
//Må ta i bruk ordre for å heise heisen i den retningen som er ønskelig.

//Trenger å initialize


//Polle etter
