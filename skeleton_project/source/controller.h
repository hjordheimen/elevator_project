
//Tilstandene vi kan komme i

typedef enum state{
    IDLE,
    GOING_UP,
    GOING_DOWN,
    HALT
}state_t;

//Hva skal skje når vi ankommer, er i, eller går ut fra en tilstand, state.

typedef enum action {
    ENTER,
    INSIDE,
    EXIT
}action_t;

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

void update_current_floor();

void next_state(state next_state, action next_action);

state get_next_state();

//Ser hvor vi er i systemet, hvilken etasje

int get_current_floor();

void read_buttons();

void stop();
