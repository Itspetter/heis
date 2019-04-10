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
int order_check_for_order(void);

//skal legge 1 på plassen i orders-arrayet som tilhører button og floor.
void order_place_orders(elev_button_type_t button, int floor);

void order_update(void); 

//Alle bestillinger som skal til den eStasjen slettes
void order_erase_order(int floor);

//Sjekker om det er bestillinger i samme etasje
int order_same_floor_order(int floor);

int order_is_order_same_direction(int floor, elev_motor_direction_t dir);

int order_only_one_order(); 

elev_motor_direction_t order_get_direction(int floor, elev_motor_direction_t direction);



#endif /* order_h */
