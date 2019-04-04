//
//  order.h
//  Heis
//
//  Created by Hanna Hjelmeland on 26/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//

#include "elev.h"

#ifndef order_h
#define order_h


//befinner oss i in_floor. Sjekk på for å finne ut om vi skal gå til moving eller idle.
int order_check_for_order();

//skal legge 1 på plassen i order-arrayet som tilhører button og floor.
void order_place_order(elev_button_type_t button, int floor);

//Alle bestillinger som skal til den etasjen slettes
void order_erase_order(int floor);

//Sjekker om det er bestillinger i samme etasje
int order_same_floor_order(int floor);

int order_order_below(int floor);

int order_order_above(int floor);

int order_is_order_same_dir(int floor, elev_motor_direction_t dir);

int order_cab_order_above(int floor);
int order_cab_order_below(int floor);
int order_cab_order_in_floor(int floor);
elev_motor_direction_t order_get_dir(int floor, elev_motor_direction_t direction);

#endif /* order_h */
