#include "elev.h"
#include "order.h"
#include "fsm.h"
#include <stdio.h>


/*FUNKSJONER VI VIL HA
 *order_check_for_order();
 *order_place_order(elev_button_type_t button, int floor) skal legge 1 på plassen i order-arrayet som tilhører button og floor.
 *order_erase_order(int floor) Alle bestillinger som skal til den etasjen slettes
 *fsm_emergency_handler() som kaller order_erase_all() {(0-3) erase_order}
 *
 */

int orders[N_FLOORS*N_BUTTONS];



typedef enum state_id { //hvorfor forskjellig navn på enum og identifier
    idle = 0, //I ro uten bestillinger
    in_floor, //I ro, åpne dør, sjekke bestilling
    moving, //Beveger seg mot prioritert bestilling
    emergency_stop
} state;

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    state current_state = idle;
    
    while (1) {
        //Sjekk på stoppknapp for hver iterasjon
        if(elev_get_stop_signal()) {
            current_state = emergency_stop;
        }
        
        //Legg inn bestilling hvis en eller flere knapper trykkes
        fsm_check_buttons_place_order(orders);
        
        //Hvis i etasje, slett alle betillinger i samme etasje
        int floor = elev_get_floor_sensor_signal();
        if(floor != -1) {
            if(orders[N_BUTTONS*floor] || orders[N_BUTTONS*floor + 1] ) {
                fsm_open_door(orders);
            }
            order_erase_order(floor, orders);
        }
        
        
        switch(current_state) {
            case(idle): {
                if(order_check_for_order(orders)){
                    
                    current_state = moving;
                }
            }
            case(in_floor): {
                printf("In floor");
                break;
            }
            case(moving) : {
                printf("In floor");
                break;
            }
            case(emergency_stop) : {
                fsm_emergency_handler(orders);
                break;
            }
            default : {
                return 0;
            }
        }
        
        
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

    }

    return 0;
}
