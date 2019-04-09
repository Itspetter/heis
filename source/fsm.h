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

typedef enum state_id { 
    idle = 0, //I ro uten bestillinger
    open_door, //I ro, åpne dør, sjekke bestilling
    moving, //Beveger seg mot prioritert bestilling
    emergency_stop
} state;

elev_motor_direction_t direction;

void fsm_emergency_handler(void);

void fsm_open_door(void);

void fsm_timeout(void);

void fsm_order_in_current_floor(void);

void fsm_start_moving(void); 

void fsm_order_in_last_floor(void);

void fsm_fsm(void);

#endif /* fsm_h */
