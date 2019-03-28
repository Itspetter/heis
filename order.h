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


int order_check_for_order(int order[]); //befinner oss i in_floor. Sjekk på for å finne ut om vi skal gå til moving eller idle. 
void order_place_order(elev_button_type_t button, int floor, int order[]); //skal legge 1 på plassen i order-arrayet som tilhører button og floor.
void order_erase_order(int floor,  int order[]); //Alle bestillinger som skal til den etasjen slettes

#endif /* order_h */
