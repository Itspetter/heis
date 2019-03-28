//
//  order.c
//  Heis
//
//  Created by Hanna Hjelmeland on 26/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//


#include "order.h"
int order_check_for_order(int orders[]){
    for(int i = 0; i < 12; i++)
    {
        if(orders[i]) {return 1;}
    }
    return 0; 
}

void order_place_order(elev_button_type_t button, int floor, int orders[]){
    int button_value = button;
    orders[N_BUTTONS*floor + button_value] = 1;
}

void order_erase_order(int floor,  int orders[]){
    for(int i = 0; i < N_BUTTONS; i++)
    {
        orders[N_BUTTONS*floor + i] = 0;
    }
}

int order_same_floor_order(int floor, int orders[]){
    return (orders[N_BUTTONS*floor] || orders[N_BUTTONS*floor + 1] || orders[N_BUTTONS*floor + 2]);
}
