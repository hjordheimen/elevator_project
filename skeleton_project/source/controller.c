#include "hardware.h"
#include "ordre.h"
#include <stdio.h>


typedef struct state{
    IDLE
    GOING_UP
    GOING_DOWN
    AT_TOP          //Unused
    AT_BUTTON       //Unused
}state;



//Controlleren må være "føleren" som skal kjenne på sensorene til en hver tid.
//Må ta i bruk ordre for å heise heisen i den retningen som er ønskelig.

//Trenger å initialize


//Polle etter 
