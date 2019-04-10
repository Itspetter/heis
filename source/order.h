/**
 * @file 
 * @brief The order module
 * 
 */

#include "elev.h"

#ifndef order_h
#define order_h



/**
 * @brief Check the orders array for existing orders 
 * 
 * @return 1 if there is an order, 0 otherwise.
 * 
 */
int order_check_for_order(void);


/**
 * @brief Place an order in the orders array on the designated
 * spot determined by @p button and @p floor. 
 * 
 * @param [in] button Button generating the order. 
 * @param [in] floor The floor in witch the button is pressed.
 * 
 */
void order_place_orders(elev_button_type_t button, int floor);

/**
 * @brief Loop through the buttons and check if they are pressed. 
 * If so, place the generated order in the orders array. 
 * 
 */
void order_update(void); 

/**
 * @brief Erase all orders in the orders array that belongs to @p floor. 
 * 
 * @param [in] floor The floor that we want to erase all orders from.
 * 
 */
void order_erase_order(int floor);

/**
 * @brief Check if there are orders in a spesific floor. 
 * 
 * @param [in] floor The floor that we want to examine. 
 * 
 * @return 1 if there are orders in the designated floor. 0 otherwise. 
 * 
 */
int order_same_floor_order(int floor);

/**
 * @brief Check if there are orders in a spesific floor. 
 * 
 * @param [in] floor The current floor
 * @param [in] dir The current direction
 * 
 * @return 1 if the order is in the right direction corresponding to 
 * @p dir. 0 otherwise. 
 * 
 */
int order_is_order_same_direction(int floor, elev_motor_direction_t dir);

/**
 * @brief Check if there only is one order. 
 * 
 * @return 1 if there are only one order. 0 if there are zero or more than one orders. 
 * 
 */
int order_only_one_order(); 

/**
 * @brief Find the optimal direction 
 * 
 * @param [in] floor The last floor
 * @param [in] dir The last direction
 * 
 * @return @c DIRN_UP if the last direction was DIRN_UP and there are
 * orders in a floor above @p floor. @c DIRN_DOWN if the last direction was 
 * @c DIRN_UP and there are no orders in a floor above @p floor. 
 * @c DIRN_UP if the last direction was 
 * @c DIRN_DOWN and there are orders in a floor above @p floor. @c DIRN_DOWN
 * if the last direction was @c DIRN_DOWN and there are no orders 
 * in a floor above @p floor. @c DIRN_STOP if none of the above is the case.
 * 
 */
elev_motor_direction_t order_get_direction(int floor, elev_motor_direction_t direction);



#endif /* order_h */
