#include "controller.h"
#include "hardware.h"
#include "order.h"

//Her må vi finne ut hvilke knapper som har blitt trykket, for så å sette den i
// en kø,


static int queue[HARDWARE_NUMBER_OF_FLOORS];
static int next_order = -1;
static int order_on_hold = -1;



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


//Legg til i kø oppover

int get_next_order(){
    return next_order;
}


void put_order_on_hold(int new_next_order){
    if(order_on_hold == -1) order_on_hold = next_order;
    next_order = new_next_order;
}

void update_next_order(){
    if(next_order == -1 && order_on_hold != -1){
        next_order = order_on_hold;
        order_on_hold = -1;
    }
}

void add_order_request(int floor, HardwareOrder order){
    queue[floor] = hardware_order_type_bit(order); //Se om dette funker likt som hardware_order_type_bit
    hardware_command_order_light(floor, order, 1);
}

void clear_floor_orders(int floor){
    switch (queue[floor]) {
        case 0:
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
            break;
        case 1:
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
            break;
        case 2:
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
            break;
        default:
            break;
    }
    queue[floor] = -1;
    next_order = -1;
}

void clear_all_orders(){
    clear_all_order_lights();
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
        clear_floor_orders(floor);
    }
}
//Legg til i kø nedover


//Legg til i intern kø



//Ordre ferdig

//Slett alle køer

void get_button_signal(){
    /* All buttons must be polled, like this: */
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        //Ser om vi har en bestilling ovenifra
        if(hardware_read_order(f, HARDWARE_ORDER_UP) && queue[f] == -1){
            //Legg til i kø oppover
            add_order_request(f, HARDWARE_ORDER_UP);
        }
        //Ser om vi har en bestilling nedenifra
        if(hardware_read_order(f, HARDWARE_ORDER_DOWN) && queue[f] == -1){
            //Legg til i kø oppover
            add_order_request(f, HARDWARE_ORDER_DOWN);

        }
        //Ser om det er en ordre innenfra
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE) && queue[f] != 2){           //Legg til i ordre inni.
            add_order_request(f, HARDWARE_ORDER_INSIDE);
            if(queue[next_order] != 2 && queue[order_on_hold] != 2) {
                order_on_hold = f;
                update_next_order();
            }

        }
    }
}

int any_requests(){
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if (queue[floor] != -1) {
            return 1;
        }
    }
    return 0;
}


int check_floor_dir_value(int floor, int directionvalue){
    if(queue[floor] == directionvalue && next_order != floor){
        return 1;
    }
    return 0;
}
