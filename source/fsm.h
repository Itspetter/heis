
#ifndef fsm_h
#define fsm_h

#include "elev.h"
#include <time.h>

typedef enum state_id { 
    idle = 0, 
    open_door, 
    moving, 
    emergency_stop
} state;


void fsm_emergency_handler(void);

void fsm_open_door(void);

void fsm_close_door(void);

void fsm_order_in_current_floor(void);

void fsm_start_moving(void); 

void fsm_order_in_last_floor(void);

void fsm_fsm(void);

#endif /* fsm_h */


