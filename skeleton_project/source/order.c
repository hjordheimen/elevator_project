#include "queue.h"
#include "hardware.h"

//Her må vi finne ut hvilke knapper som har blitt trykket, for så å sette den i
// en kø,


//Legg til i kø oppover



//Legg til i kø nedover


//Legg til i intern kø



//Ordre ferdig

//Slett alle køer

void get_button_signal(){
    /* All buttons must be polled, like this: */
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        //Ser om vi har en bestilling ovenifra
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
            //Legg til i kø oppover
        }
        //Ser om vi har en bestilling nedenifra
        if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
            //Legg til i kø oppover
        }
        //Ser om det er en ordre innenfra
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            //Legg til i ordre inni.
        }
    }
}

int get_number_of_floors(){
    return HARDWARE_NUMBER_OF_FLOORS;
}
