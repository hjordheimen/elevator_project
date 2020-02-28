#include "hardware.h"
#include "order.h"
#include "controller.h"
#include <stdio.h>
#include <time.h>

#define CLOSING_TIME 3
#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static int last_floor = BETWEEN_FLOORS;
static HardwareMovement last_movement = HARDWARE_MOVEMENT_STOP;
static action_t action = ENTER;
static state_t state = IDLE;
static int door_time;


void initialize(){
    hardware_init();
    clear_all_orders();
    update_current_floor();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while (current_floor == BETWEEN_FLOORS) {
        update_current_floor();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    printf("Da er vi klare! :D \n\n");
}



void idle(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
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
        update_next_order();
        //OPEN DOOR for 3 seconds, Sette på en Timer.
        hardware_command_door_open(1);
        door_time = time(NULL);
        next_state(HALT, INSIDE);
            break;
        case INSIDE:
        //Hvis timeren er ferdig, hopp til exit, der vi lukker døren, og går videre.
            if(time(NULL) - door_time > CLOSING_TIME) next_state(HALT, EXIT);
            //Sette inn obstruksjonsknappen her
            obstruction(hardware_read_obstruction_signal());
            break;
        case EXIT:
        //Dørene lukkes.
        hardware_command_door_open(0);
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

static void other_on_the_way(){
    if(last_movement == HARDWARE_MOVEMENT_UP){
        for (int floor = current_floor; floor < get_next_order(); floor++){
            if (check_floor_dir_value(floor, 0)){
                put_order_on_hold(floor);
            }
        }
    }
    else{
        for (int floor = current_floor; floor > get_next_order(); floor--){
            if (check_floor_dir_value(floor, 1)){
                put_order_on_hold(floor);
            }
        }
    }
}

void obstruction(int obstruction_signal){
    if(obstruction_signal){
        door_time = time(NULL);
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
        while (hardware_read_stop_signal()) {
            if(hardware_read_floor_sensor(current_floor)) hardware_command_door_open(1);
        }
        hardware_command_stop_light(0);
        door_time = time(NULL);
        while (time(NULL) - door_time < CLOSING_TIME) {
            if(hardware_read_floor_sensor(current_floor)) obstruction(hardware_read_obstruction_signal());
        }
        hardware_command_door_open(0);
        next_state(IDLE, ENTER);
    }
    return 0;
}
