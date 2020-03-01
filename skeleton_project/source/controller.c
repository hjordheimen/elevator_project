#include "hardware.h"
#include "order.h"
#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOSING_TIME 3
#define BETWEEN_FLOORS -1

static int current_floor = BETWEEN_FLOORS;
static int previous_floor = BETWEEN_FLOORS;
static int door_time;

static HardwareMovement previous_movement = HARDWARE_MOVEMENT_STOP;

static action_t action = ENTER;
static state_t state = IDLE;



static void control_pick_up_order(){
    if(previous_movement == HARDWARE_MOVEMENT_UP){
        for (int floor = previous_floor; floor < order_get_next(); floor++){
            if (order_floor_dir_value(floor, 0)){
                order_put_on_hold(floor);
            }
        }
    }
    else{
        for (int floor = previous_floor; floor > order_get_next(); floor--){
            if (order_floor_dir_value(floor, 1)){
                order_put_on_hold(floor);
            }
        }
    }
}

static int control_closing_time(){
    if(time(NULL) - door_time > CLOSING_TIME) return 1;
    return 0;
}

static void control_set_next_state(state_t next_state, action_t next_action){
        state = next_state;
        action = next_action;
}

static void control_move_elevator(){
    if(current_floor == BETWEEN_FLOORS && previous_floor == order_get_next() && previous_movement == HARDWARE_MOVEMENT_STOP){
        previous_floor = BETWEEN_FLOORS;
        if(previous_movement == HARDWARE_MOVEMENT_UP) control_set_next_state(GOING_DOWN, ENTER);
        else control_set_next_state(GOING_UP, ENTER);
    }
    else{
        if (order_get_next() < previous_floor) {
            control_set_next_state(GOING_DOWN, ENTER);
        }
        else control_set_next_state(GOING_UP, ENTER);
    }
}

static void control_obstruction(){
    while(hardware_read_obstruction_signal()){
        door_time = time(NULL);
    }
}


void control_init(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    order_clear_all();
    control_update_current_floor();
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while (previous_floor == BETWEEN_FLOORS) {
        control_update_current_floor();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    printf("Da er vi klare! :D \n\n");
}



void idle(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    previous_movement = HARDWARE_MOVEMENT_STOP;
    if (order_any_requests()) control_move_elevator();
}

void go_up(){
    switch (action) {
        case ENTER:
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            previous_movement = HARDWARE_MOVEMENT_UP;
            control_set_next_state(GOING_UP, INSIDE);
            break;
        case INSIDE:
            control_pick_up_order();
            if (previous_floor == order_get_next()) {
                control_set_next_state(HALT, ENTER);
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
            previous_movement = HARDWARE_MOVEMENT_DOWN;
            control_set_next_state(GOING_DOWN, INSIDE);
            break;
        case INSIDE:
            control_pick_up_order();
            if (previous_floor == order_get_next()) {
                control_set_next_state(HALT, ENTER);
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
            previous_movement = HARDWARE_MOVEMENT_STOP;
            hardware_command_floor_indicator_on(previous_floor);
            order_clear_floor(previous_floor);
            order_update_next();
            hardware_command_door_open(1);
            door_time = time(NULL);
            control_set_next_state(HALT, INSIDE);
            break;
        case INSIDE:
            control_obstruction();
            if(control_closing_time()) control_set_next_state(HALT, EXIT);
            break;
        case EXIT:
            hardware_command_door_open(0);
            if (order_get_next() == -1) {
                control_set_next_state(IDLE, ENTER);
            }
            else if(order_get_next() < previous_floor){
                control_set_next_state(GOING_DOWN, ENTER);
            }
            else{
                control_set_next_state(GOING_UP, ENTER);
            }
            break;
        default:
        break;

    }

}

state_t control_next_state(){
    return state;
}


void control_update_current_floor(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if(hardware_read_floor_sensor(floor)) {
            current_floor = floor;
            previous_floor = current_floor;
        }
        else current_floor = BETWEEN_FLOORS;
    }
}


void control_read_buttons(){
    order_pull_buttons();
}

void control_stop(){
    if(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        previous_movement = HARDWARE_MOVEMENT_STOP;
        order_clear_all();
        hardware_command_stop_light(1);
        while (hardware_read_stop_signal()) {
            if(hardware_read_floor_sensor(current_floor)) hardware_command_door_open(1);
        }
        hardware_command_stop_light(0);
        door_time = time(NULL);
        while (!control_closing_time()) {
            if(hardware_read_floor_sensor(current_floor)) control_obstruction();
        }
        hardware_command_door_open(0);
        control_set_next_state(IDLE, ENTER);
    }
}
