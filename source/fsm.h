//
//  fsm.h
//  Heis
//
//  Created by Hanna Hjelmeland on 28/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//

#ifndef fsm_h
#define fsm_h

#include "elev.h"
#include <time.h>



void fsm_emergency_handler();

void fsm_check_buttons_place_order();

void fsm_open_door();

void fsm_timeout();

//SKRIV OM DENNE!
int fsm_is_order_in_same_floor() ;



#endif /* fsm_h */
