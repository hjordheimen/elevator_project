



//Neste ordre

void next_order();


//Bestill ordre oppover

void add_order_request(int floor, HardwareOrder order);

//Slett alle ordre på en gitt etasje

void clear_floor_orders(int floor);

//Slett alle ordre

void clear_all_orders();

//Ser om det er noen inkommende ordre.


void get_button_signal();

int get_number_of_floors();
