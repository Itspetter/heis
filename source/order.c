//
//  order.c
//  Heis
//
//  Created by Hanna Hjelmeland on 26/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//



int orders[12];

#include "order.h"
int order_check_for_order(){
    for(int i = 0; i < 12; i++)
    {
        if(orders[i]) {return 1;}
    }
    return 0; 
}

void order_place_order(elev_button_type_t button, int floor){
    int button_value = button;
    orders[N_BUTTONS*floor + button_value] = 1;
}

void order_erase_order(int floor){
    //HVIS IKKE I ETASJE - IKKE HANDLE
    if(floor == -1) { return; }
    for(int i = 0; i < N_BUTTONS; i++)
    {
        if(floor == 0 && i == 1) { 
            continue; 
        }
        if(floor == 3 && i == 0) { 
            continue;  
        }
        orders[N_BUTTONS*floor + i] = 0;
        elev_set_button_lamp(i,floor,0);
    }
}

int order_same_floor_order(int floor){
    if(floor == -1) { return 0; }
    return (orders[N_BUTTONS*floor] || orders[N_BUTTONS*floor + 1] || orders[N_BUTTONS*floor + 2]);
}


//HUSK: MÅ SENDE INN LAST FLOOR
int order_order_below(int floor) {
    for(int i = 0; i < floor; i++) {
        if(order_same_floor_order(i)) { 
            return 1; 
        }
    }
    return 0;
}

int order_order_above(int floor) {
    for(int i = floor +1; i <= N_FLOORS; i++) {
        if(order_same_floor_order(i)) { 
            return 1; 
        }
    }
    return 0;
}