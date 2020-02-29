#include "hardware.h"
#include "order.h"



static int queue[HARDWARE_NUMBER_OF_FLOORS];
static int next_order = -1;
static int order_on_hold = -1;



static void order_clear_all_lights(){
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


static void order_add_request(int floor, HardwareOrder order){
    hardware_command_order_light(floor, order, 1);
    queue[floor] = hardware_order_type_bit(order);

}


int order_get_next(){
    return next_order;
}


void order_put_on_hold(int new_next_order){
    if(order_on_hold == -1) order_on_hold = next_order;
    next_order = new_next_order;
}

void order_update_next(){
    if(next_order == -1 && order_on_hold > -1){
        next_order = order_on_hold;
        order_on_hold = -1;
    }
}


void order_clear_floor(int floor){
    hardware_command_order_light(floor, HARDWARE_ORDER_UP,0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE,0);
    queue[floor] = -1;
    next_order = -1;
}

void order_clear_all(){
    order_clear_all_lights();
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        order_clear_floor(floor);
    }
}
void order_pull_buttons(){
    /* All buttons must be polled, like this: */
    for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        //Ser om vi har en bestilling ovenifra
        if(hardware_read_order(floor, HARDWARE_ORDER_UP)){
            //Legg til i kø oppover
            if(queue[floor] == -1){
                order_add_request(floor, HARDWARE_ORDER_UP);
                if(queue[order_on_hold] == -1) {
                    order_on_hold = floor;
                    order_update_next();
                }
            }
            else hardware_command_order_light(floor, HARDWARE_ORDER_UP,1);
        }
        //Ser om vi har en bestilling nedenifra
        if(hardware_read_order(floor, HARDWARE_ORDER_DOWN)){
            //Legg til i kø oppover
            if(queue[floor] == -1){
            order_add_request(floor, HARDWARE_ORDER_DOWN);
                if(queue[order_on_hold] == -1) {
                    order_on_hold = floor;
                    order_update_next();
                }
            }
            else hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        //Ser om det er en ordre innenfra
        if(hardware_read_order(floor, HARDWARE_ORDER_INSIDE) && queue[floor] != 2){
            order_add_request(floor, HARDWARE_ORDER_INSIDE);
            if(queue[next_order] != 2 && queue[order_on_hold] != 2) {
                order_on_hold = floor;
                order_update_next();
            }

        }
    }
}

int order_any_requests(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if (queue[floor] > -1) {
            next_order = floor;
            return 1;
        }
    }
    return 0;
}


int order_floor_dir_value(int floor, int dir_value){ //Sette dir_value til en HardwareOrder type
    if(queue[floor] == dir_value && next_order != floor){
        return 1;
    }
    return 0;
}
