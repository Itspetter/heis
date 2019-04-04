//
//  fsm.c
//  Heis
//
//  Created by Hanna Hjelmeland on 28/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//

#include <stdio.h>
#include "fsm.h"
#include "order.h"
#include "timer.h"
#include "elev.h"



void fsm_emergency_handler() {
    //STOPPLAMPE OG MOTOR
    elev_set_stop_lamp(1);
    elev_set_motor_direction(DIRN_STOP);
    
    //SLETTE ALLE BESTILLINGER
    for(int i = 0; i < N_FLOORS; i++) {
        order_erase_order(i);
    }
    
    //Hvis i etasje og døren er lukket, åpne døren
    if((elev_get_floor_sensor_signal() != (-1)) && timer_timeout()) {
        fsm_open_door();
    }
    
    //LOOPER TIL KNAPP IKKE LENGER ER TRYKKET
    while(elev_get_stop_signal());
    elev_set_stop_lamp(0);
    
}

void fsm_check_buttons_place_order() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++){
            if(!((i == 0 && j == 3) || (i == 1 && j == 0))) {
                if(elev_get_button_signal(i, j)) {
                    order_place_order(i, j);
                    elev_set_button_lamp(i,j,1);
                }
            }
        }
    }
}

void fsm_open_door() {
    timer_start();
    elev_set_door_open_lamp(1);
}


void fsm_timeout() {
    elev_set_door_open_lamp(0);
    timer_stop(); 
}

void fsm_order_in_current_floor() {
    order_erase_order(elev_get_floor_sensor_signal());
    fsm_open_door();
}