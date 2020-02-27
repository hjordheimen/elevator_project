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

 /**
 * @brief state type is used in switch-case in main, and as a global variable
 * next_state.
 */
typedef enum state{
    IDLE,
    GOING_UP,
    GOING_DOWN,
    HALT
}state_t;

/**
* @brief action type is used to keep the state machine/elevator aware of if it
* is entering a state, already inside a state, or exiting a state.
*
* Swtiching action happens in different states depending on different inputs.
*/
typedef enum action {
    ENTER,
    INSIDE,
    EXIT
}action_t;

//Initialiserer heisen, Der vi kommer i en tilstand
/**
* @brief Initializes the hardware, resets the orders and lighting.
*
* Orientate itself by going down, while looking for a valid floor.
*
* When done: Entering IDLE-mode
*/

void initialize();

//Kjør IDLE-tilstanden,

/**
* @brief The elevator is standing still, and continously looking for new requests
*/

void idle();

//Kjør GOING_UP-tilstanden

/**
* @brief takes the elevator up towards the ordered request.
*/

void go_up();

// Kjør GOING_DOWN-tilstanden
/**
* @brief takes the elevator down towards the ordered request.
*/

void go_down();

//Kjør HALT-tilstanden
/**
* @brief When the elevator reaches the requested floor,
* it halts, opens the door for 3 seconds, let passangers go on & off, closes the door,
* and are ready for the next order.
*
* When done: Order is cleared from the orderlist
*/


void halt();

/**
* @brief updates the global value @c current_floor
* Uses the @c hardware_read_floor_sensor to orientate the elevator
*/


void update_current_floor();

/**
* @brief Sets the next state, and with the occuring action depending on the switch
*/


void next_state(state_t next_state, action_t next_action);

/**
* @brief Gives all the modules listening to controller a function to get the state.
*
*/


state_t get_next_state();

/**
* @brief While the door is open, and the obstruction flicker is on, then the whole
* elevator freezes.
*
* @param obstruction_signal from @c hardware_read_obstruction_signal which is 1 or 0.
*/

void obstruction(int obstruction_signal);

/**
* @brief returns the current_floor
*/


int get_current_floor();

/**
* @brief Uses @c get_button_signal from the order module.
*
* Makes the connection between main and order.
*/

int read_buttons();

/**
* @brief stops the elevator, clears all the orders.
*
* If at a valid floor: opens the door.
*/

int stop();
