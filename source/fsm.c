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

int current_floor;
int last_floor; 


void fsm_emergency_handler() {
    elev_set_stop_lamp(1);
    elev_set_motor_direction(DIRN_STOP);
    
    for(int i = 0; i < N_FLOORS; i++) {
        order_erase_order(i);
    }
    
    //Hvis i etasje og døren er lukket, åpne døren
    if((current_floor != -1) && timer_timeout()) {
        fsm_open_door();
    }
    
    while(elev_get_stop_signal());
    elev_set_stop_lamp(0);
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
    order_erase_order(current_floor);
    fsm_open_door();
}

void fsm_start_moving() {
    elev_motor_direction_t prev_direction = direction;
    direction = order_get_dir(current_floor, prev_direction);
    elev_set_motor_direction(direction);
}

void fsm_order_in_last_floor() {
    if(direction == DIRN_DOWN) {
        elev_set_motor_direction(DIRN_UP);
    }
    else {
        elev_set_motor_direction(DIRN_DOWN);
    }
}


void fsm_fsm(){

    state current_state = idle;

    current_floor = elev_get_floor_sensor_signal();
    last_floor = current_floor;

    while (1) {

        if(elev_get_stop_signal()) {
            fsm_emergency_handler();
            current_state = emergency_stop;
        }

        order_update();
        
        current_floor = elev_get_floor_sensor_signal();

        if(current_floor != -1) {
            last_floor = current_floor;
            elev_set_floor_indicator(current_floor);
        }
        
        
        switch(current_state) {
            case(idle): {
                if(order_check_for_order()){
                    if(order_same_floor_order(current_floor)){
                        fsm_order_in_current_floor();
                        current_state = open_door;
                    }
                    else{
                        //HVIS NØDSTOPP TRYKKES MELLOM TO ETASJER
                        //MÅ SNU RETNING TILBAKE
                        if (order_same_floor_order(last_floor)) {
                            fsm_order_in_last_floor();
                        }
                        else {
                            if(order_order_above(last_floor)) {
                                elev_set_motor_direction(DIRN_UP);
                                direction = DIRN_UP;
                            }
                            else {
                                elev_set_motor_direction(DIRN_DOWN);
                                direction = DIRN_DOWN;
                            }
                        }
                        current_state = moving;
                    } 
                }
                else {
                    current_state = idle;
                }
                break;
            }
            case(open_door): {
                if(order_same_floor_order(current_floor)){
                    fsm_order_in_current_floor();
                    current_state = open_door;
                }
                if(timer_timeout()) {
                    fsm_timeout();
                    if(order_check_for_order()) {
                        if(order_same_floor_order(current_floor)){
                            fsm_order_in_current_floor();
                            current_state = open_door;
                        }
                        else {
                            fsm_start_moving();
                            current_state = moving; 
                        }
                    }   
                    else {
                        current_state = idle;
                    }
                }
                else { 
					current_state = open_door; 
				}
                break;
            }
            case(moving): {
                if(order_same_floor_order(current_floor) && order_is_order_same_dir(current_floor, direction)) {
                    elev_set_motor_direction(DIRN_STOP);
                    fsm_order_in_current_floor();
                    current_state = open_door; 
                }
                break;
            }
            case(emergency_stop): {
                if(current_floor != -1) {
                    fsm_order_in_current_floor();
                    current_state = open_door;
                }
                else {
                    current_state = idle; 
                }
                break;
            }
            default: {
                return;
            }
        }
    }
}