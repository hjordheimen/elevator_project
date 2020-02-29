#include <stdio.h>
#include <limits.h>
#include <signal.h>
#include "controller.h"


static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    signal(SIGINT, sigint_handler);
    control_init();

    while(1){
        switch (control_next_state()) {
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
        control_read_buttons();
        control_update_current_floor();
        control_stop();
    }

    return 0;
}
