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
#include "order.h"
#include <time.h>

void fsm_emergency_handler(int order[]);

void fsm_check_buttons_place_order(int orders[]);

void fsm_open_door(int orders[]);



#endif /* fsm_h */
