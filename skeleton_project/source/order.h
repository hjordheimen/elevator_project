
//Bestill ordre oppover

void add_order_request_up(int floor);

//Bestill ordre nedover

void add_order_request_down(int floor);

//Hvor skal bestilingen

void set_order(int floor);

//Slett alle ordre

void clear_all_orders();

//Slett ordre

void remove_order();

//Ser om det er noen inkommende ordre.

void look_for_requests();

//Poller om det er noe signal å hente, både requests opp, ned, eller inni.

void get_button_signal();

int get_number_of_floors();
