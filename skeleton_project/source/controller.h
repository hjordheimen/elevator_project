/**
 * @file
 * @brief controller is the controlling unit for the elevator. It is build up as
 * a state machine, where it can hold 4 types of states, and have up to 3 actions
 * to do while in a specific state.
 *
 * Controller is where the magic happens ;) 
 *
 * Henrik Jordheim
 */
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

void next_state(state_t next_state, action_t next_action);

state_t get_next_state();

//Ser hvor vi er i systemet, hvilken etasje

void obstruction(int obstruction_signal);

int get_current_floor();

int read_buttons();

int stop();
