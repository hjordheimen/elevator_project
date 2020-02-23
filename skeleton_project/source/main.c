#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include "hardware.h"
#include "controller.h"

// static void clear_all_order_lights(){
//     HardwareOrder order_types[3] = {
//         HARDWARE_ORDER_UP,
//         HARDWARE_ORDER_INSIDE,
//         HARDWARE_ORDER_DOWN
//     };
//
//     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
//         for(int i = 0; i < 3; i++){
//             HardwareOrder type = order_types[i];
//             hardware_command_order_light(f, type, 0);
//         }
//     }
// }





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
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    printf("NU KØR VI!\n");

    initialize();

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
            case HALT:
                halt();
                break;
        }
        read_buttons();
        update_current_floor();
        printf("%d\n", get_current_floor();
    }

    return 0;
}
