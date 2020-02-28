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
 * @dependencies hardware, controller
 *
 * Henrik Jordheim
 */



/**
* @brief Takes the current order, and puts it on hold, and takes on the next order.
*
* @param new_next_order is an order of HardwareOrder
*/


void put_order_on_hold(int new_next_order);


/**
* @brief updates the orders. If there isn't any next order, see if we got any on hold.
*/

void update_next_order();


/**
* @brief adds an order to a given floor.
*
* @param floor is the floor where the elevator is wanted
* @param order is where the elevator should go afterwards
*/

void add_order_request(int floor, HardwareOrder order);

/**
* @brief when the order is done, the floor-order is cleared (set to -1).
*
* @param floor is the floor to be cleared
*/

void clear_floor_orders(int floor);

/**
* @brief clear all orders at every floor. Uses clear_floor_orders
*
*/

void clear_all_orders();

/**
* @brief polls orders, takes orders depending on the direction or INSIDE the elevator.
* If there is an order already at a floor, nothing happens (Unless there is an INSIDE request)
*/

void get_button_signal();

/**
* @brief returns a 1 if there is more orders to dispatch, else returns 0
*
*/

int any_requests();

/**
* @brief looks at a floor with the same direction value as the current order.
* returns a 1 if the floor is different than the current order, else 0
*
* @param floor indicates the floor wich is evalueted in the direction the order is at
* @param directionvalue is FYLLL INN MER HER!!
*/


int check_floor_dir_value(int floor, int directionvalue);
