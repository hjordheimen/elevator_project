



//Neste ordre

void next_order();


//Bestill ordre oppover

void add_order_request(int floor, HardwareOrder order);

//Hvor skal bestilingen

void set_order(int floor);

//Slett alle ordre på en gitt etasje

void clear_floor_orders(int floor);

//Slett alle ordre

void clear_all_orders();

//Ser om det er noen inkommende ordre.

void look_for_requests();

//Poller om det er noe signal å hente, både requests opp, ned, eller inni.

void get_button_signal();

int get_number_of_floors();
