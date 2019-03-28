#include "elev.h"
#include "order.h"
#include <stdio.h>

/*FUNKSJONER VI VIL HA
 *order_check_for_order();
 *order_place_order(elev_button_type_t button, int floor) skal legge 1 på plassen i order-arrayet som tilhører button og floor.
 *order_erase_order(int floor) Alle bestillinger som skal til den etasjen slettes
 *fsm_emergency_handler() som kaller order_erase_all() {(0-3) erase_order}
 *
 */

void emergency_handler(int order[]) {
    //STOPPLAMPE OG MOTOR
    elev_set_stop_lamp(1);
    elev_set_motor_direction(DIRN_STOP);
    
    //SLETTE ALLE BESTILLINGER
    for(int i = 0; i < N_FLOORS; i++) {
        order_erase_order(i, order);
    }
    
    //LOOPER TIL KNAPP IKKE LENGER ER TRYKKET
    while(elev_get_stop_signal());
    elev_set_stop_lamp(0);
}



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    

    typedef enum state_id { //hvorfor forskjellig navn på enum og identifier
        idle = 0, //I ro uten bestillinger
        in_floor, //I ro, åpne dør, sjekke bestilling
        moving, //Beveger seg mot prioritert bestilling
        emergency_stop
    } state;
    
    state current_state = idle;
    int orders[12];
    
    while (1) {
        
        
        
        
        switch(current_state) {
            case(idle): {
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
                emergency_handler(orders);
                break;
            }
            default : {
                
            }
        }
        
        
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
