/**
 * @file 
 * @brief Finite state machine module
 * 
 */

#ifndef fsm_h
#define fsm_h

#include "elev.h"

/**
 *  @brief Possible states for the fsm.
 * 
 */
typedef enum state { 
    idle = 0, 
    open_door, 
    moving, 
    emergency_stop
} state_id;

/**
 * @brief Decide if next state is open door or moving based on 
 * which floor the order is in. 
 */
void fsm_handle_order(void);



/**
 * @brief Take care of emergencies. Stops motor, erases orders, 
 * and opens door if the elevator is in a floor.
 */
void fsm_emergency_handler(void);

/**
 * @brief Start the timer and turn on the open door lamp.
 * 
 */
void fsm_open_door(void);

/**
 * @brief Turn off the open door lamp and stop the timer.
 * 
 */
void fsm_close_door(void);

/**
 * @brief Delete orders in the floor you are in and open the door.
 * 
 */
void fsm_delete_order_open_door(void);

/**
 * @brief Set the direction of the motor in the right direction 
 * according to where there are orders to be taken. Start the motor.
 *  
 * Special case: If startup after emergency between two floors and order
 * in the previous floor -> change direction previous direction. 
 */
void fsm_start_moving(void); 

/**
 * @brief Run the finite state machine.
 * 
 */
void fsm_run(void);

#endif /* fsm_h */


