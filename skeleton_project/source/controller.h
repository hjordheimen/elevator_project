
//Tilstandene vi kan komme i

typedef enum states{
    IDLE,
    GOING_UP,
    GOING_DOWN,
    HALT
}state;

//Hva skal skje når vi ankommer, er i, eller går ut fra en tilstand, state.

typedef enum action {
    ENTER,
    INSIDE,
    EXIT
}action;

//Initialiserer heisen, Der vi kommer i en tilstand

void initialize();

//Kjør IDLE-tilstanden,

void idle();

//Kjør GOING_UP-tilstanden

void go_up();

// Kjør GOING_DOWN-tilstanden

void go_down();

//Kjør HALT-tilstanden

void halt();

//Ser hvor vi er i systemet, hvilken etasje

int get_current_floot();
