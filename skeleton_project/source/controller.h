
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

void idle(action action);

//Kjør GOING_UP-tilstanden

void go_up(action action);

// Kjør GOING_DOWN-tilstanden

void go_down(action action);

//Kjør HALT-tilstanden

void halt(action action);

//Ser hvor vi er i systemet, hvilken etasje

int get_current_floor();
