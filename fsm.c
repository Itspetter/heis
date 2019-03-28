//
//  fsm.c
//  Heis
//
//  Created by Hanna Hjelmeland on 28/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//

#include <stdio.h>
#include "fsm.h"

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

void fsm_check_buttons_place_order(int orders[]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++){
            if(elev_get_button_signal(i, j)) {
                order_place_order(i, j, orders);
            }
        }
    }
}
