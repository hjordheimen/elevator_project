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
* @brief returns the next order (if there is any).
*/

int order_get_next();

/**
* @brief Takes the current order, and puts it on hold, and takes on the next order.
*
* @param new_next_order is an order of HardwareOrder
*/


void order_put_on_hold(int new_next_order);


/**
* @brief updates the orders. If there isn't any next order, see if we got any on hold.
*/

void order_update_next();


/**
* @brief when the order is done, the floor-order is cleared (set to -1).
*
* @param floor is the floor to be cleared
*/

void order_clear_floor(int floor);

/**
* @brief clear all orders at every floor. Uses order_clear_floor
*
*/

void order_clear_all();

/**
* @brief polls orders, takes orders depending on the direction or INSIDE the elevator.
* If there is an order already at a floor, nothing happens (Unless there is an INSIDE request)
*/

void order_pull_buttons();

/**
* @brief returns a 1 if there is more orders to dispatch, else returns 0
*
*/

int order_any_requests();

/**
* @brief looks at a floor with the same direction value as the current order.
* returns a 1 if the floor is different than the current order, else 0
*
* @param floor indicates the floor wich is evalueted in the direction the order is at
* @param dir_value is FYLLL INN MER HER!!
*/


int order_floor_dir_value(int floor, int dir_value);
