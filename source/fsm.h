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

void fsm_open_door();

void fsm_timeout();

int fsm_should_handle();

void fsm_order_in_current_floor();

#endif /* fsm_h */
