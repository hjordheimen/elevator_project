/**
 * @file
 * @brief Order takes care for the order-handling in the elevator project.
 * It is constructed of a list, where the length of the list is the number of floors.
 *
 * The orders occur on which floor you want to go to, if you want to go up/down --> 0/1.
 * The orderlist takes into account that you want to go up/down, and respects the
 * INSIDE orders to perform as a priority, but takes on orders that want to go in
 * the same direction.
 *
 * @Dependencies hardware, controller
 *
 * Henrik Jordheim
 */



//Neste ordre

int get_next_order();

void put_order_on_hold(int new_next_order);

void update_next_order();


//Bestill ordre oppover

void add_order_request(int floor, HardwareOrder order);

//Slett alle ordre på en gitt etasje

void clear_floor_orders(int floor);

//Slett alle ordre

void clear_all_orders();

//Ser om det er noen inkommende ordre.


void get_button_signal();

int any_requests();

int check_floor_dir_value(int floor, int directionvalue);
