#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include "hardware.h"
#include "controller.h"






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
        stop();
    }

    return 0;
}
