#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include "hardware.h"
#include "controller.h"

static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}





static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    while(1){
        /* Lights are set and cleared like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders */
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            }

            /* Orders going up */
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }

            /* Orders going down */
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            }
        }

        if(hardware_read_obstruction_signal()){
            hardware_command_stop_light(1);
            clear_all_order_lights();
        }
        else{
            hardware_command_stop_light(0);
        }
    }

    while(1){
        switch (get_next_state()) {
            case IDLE:
                idle();
                break;
            case GOING_UP:
                go_up();
                break;
            case GOING_DOWN:
                go_down();
                break;
            case HALT;
                halt();
                break;
        }
        read_buttons();
        update_current_floor();
    }

    return 0;
}
