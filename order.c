//
//  order.c
//  Heis
//
//  Created by Hanna Hjelmeland on 26/03/2019.
//  Copyright © 2019 Hanna Hjelmeland. All rights reserved.
//


#include "order.h"
int order_check_for_order(int order[]){
    for(int i = 0; i < 12; i++)
    {
        if(order[i]) {return 1;}
    }
    return 0; 
}

void order_place_order(elev_button_type_t button, int floor, int order[]){
    int button_value = button;
    order[N_BUTTONS*floor + button_value] = 1;
}

void order_erase_order(int floor,  int order[]){
    for(int i = 0; i < N_BUTTONS; i++)
    {
        order[N_BUTTONS*floor + i] = 0;
    }
}
