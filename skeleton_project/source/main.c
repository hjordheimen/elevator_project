#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"


/**
Her er det noe tekst
*/


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");



    while(1){
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        printf("%d\n", hardware_read_floor_sensor(0));

    }
}
