



//Neste ordre

void get_next_order();

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
