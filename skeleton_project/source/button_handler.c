#include "button_handler.h"

void get_button_signal(){
    /* All buttons must be polled, like this: */
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        //Ser om vi har en bestilling ovenifra
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){

        }
        //Ser om vi har en bestilling nedenifra
        if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){

        }
        //Ser om det er en ordre innenfra
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            
        }
    }
}
