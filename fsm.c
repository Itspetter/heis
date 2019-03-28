//
//  fsm.c
//  Heis
//
//  Created by Hanna Hjelmeland on 28/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//

#include <stdio.h>
#include "fsm.h"

void emergency_handler(int orders[]) {
    //STOPPLAMPE OG MOTOR
    elev_set_stop_lamp(1);
    elev_set_motor_direction(DIRN_STOP);
    
    //SLETTE ALLE BESTILLINGER
    for(int i = 0; i < N_FLOORS; i++) {
        order_erase_order(i, orders);
    }
    
    //Åpner døren hvis i etasje
    if(elev_get_floor_sensor_signal()) {
        elev_set_door_open_lamp(1);
    }
    //LOOPER TIL KNAPP IKKE LENGER ER TRYKKET
    while(elev_get_stop_signal());
    elev_set_stop_lamp(0);
    
    //Sjekker på om i etasje - holder døren åpen i ytterligere 3 sek
    if(elev_get_floor_sensor_signal()) {
        fsm_open_door(orders);
    }
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

void fsm_open_door(int orders[]) {
    time_t start_time = time(NULL);
    time_t seconds = 0;
    elev_set_door_open_lamp(1);
    while(seconds - start_time < 3) {
        //Sjekk på stoppknapp for hver iterasjon
        //?TA HØYDE FOR REKURSJON? SE PÅ DETTE
        if(elev_get_stop_signal()) {
            fsm_emergency_handler(orders);
        }
        //Legg inn bestilling hvis en eller flere knapper trykkes
        fsm_check_buttons_place_order(orders);
        seconds = time(NULL);
    }
    elev_set_door_open_lamp(0);
}
