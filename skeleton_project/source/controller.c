#include "hardware.h"
#include "order.h"
#include "controller.h"
#include <stdio.h>
#include <time.h>

#define CLOSING_TIME 3
#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static HardwareMovement last_movement = HARDWARE_MOVEMENT_STOP;
static action_t action = ENTER;
static state_t state = IDLE;


void initialize(){
    update_current_floor();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while (current_floor == BETWEEN_FLOORS) {
        update_current_floor();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    printf("Da er vi klare! :D \n\n");
}



void idle(){
    if (any_requests()) {
        if (get_next_order() < current_floor) {
            next_state(GOING_DOWN, ENTER);
        }
        else next_state(GOING_UP, ENTER);
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
            for (int floor = current_floor; floor < get_next_order(); floor++){
                if (check_floor_dir_value(floor, 0)){
                    put_order_on_hold(floor);
                }
            }
            if (current_floor == get_next_order()) {
                next_state(HALT, ENTER);
            }
            break;
        default:
        break;
}
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
        if (current_floor == get_next_order()) {
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
        hardware_command_floor_indicator_on(current_floor);
        clear_floor_orders(current_floor);
        //OPEN DOOR for 3 seconds, Sette på en Timer.
        hardware_command_door_open(1);
        int door_time = time(NULL);
        next_state(HALT, INSIDE);
            break;
        case INSIDE:
        //Hvis timeren er ferdig, hopp til exit, der vi lukker døren, og går videre.
            if(time(NULL) - door_time > CLOSING_TIME) next_state(HALT, EXIT);
            break;
        case EXIT:
        //Dørene lukkes.
        hardware_command_door_open(0);
        update_next_order();
        if (get_next_order() == -1) {
            next_state(IDLE, ENTER);
        }
        else if(get_next_order() < current_floor){
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

void update_current_floor(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if(hardware_read_floor_sensor(floor)) current_floor = floor;
    }
}

void next_state(state_t next_state, action_t next_action){
        state = next_state;
        action = next_action;
}

state_t get_next_state(){
    return state;
}


int get_current_floor(){
    return current_floor;
}

int read_buttons(){
    get_button_signal();
    return 0;
}

int stop(){
    if(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        clear_all_orders();
        hardware_command_stop_light(1);
        if(hardware_read_floor_sensor(current_floor)) hardware_command_door_open(1);
        while (hardware_read_stop_signal()) {
            //Do nothing
        }
        hardware_command_door_open(0);
        int stop_delay = time(NULL);
        while (time(NULL) - stop_delay < CLOSING_TIME) {
            //Do nothing
        }
        next_state(IDLE, ENTER);
    }
    return 0;
}


//Controlleren må være "føleren" som skal kjenne på sensorene til en hver tid.
//Må ta i bruk ordre for å heise heisen i den retningen som er ønskelig.

//Trenger å initialize


//Polle etter
