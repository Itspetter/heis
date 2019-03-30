#include "elev.h"
#include "order.h"
#include "fsm.h"
#include "timer.h"
#include <stdio.h>

typedef enum state_id { //hvorfor forskjellig navn på enum og identifier
    idle = 0, //I ro uten bestillinger
    open_door, //I ro, åpne dør, sjekke bestilling
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
        fsm_check_buttons_place_order();
        
        int floor = elev_get_floor_sensor_signal();
        
        
        switch(current_state) {
            case(idle): {
                printf("Idle");
                //
                if(order_check_for_order()){
                    if(fsm_is_order_in_same_floor){
                        //Hvis bestilling i samme etg, åpne dør og slett bestilling
                        order_erase_order(elev_get_floor_sensor_signal());
                        fsm_open_door();
                        current_state = open_door;
                    }
                    else{ current_state = moving;} 
                }
                break;
            }
            case(open_door): {
                //HUSK: ANTA AT DØR _ER_ ÅPEN NÅR DU KOMMER HIT!
                printf("Open Door");
                //HVIS DØREN SKAL LUKKES
                if(timer_timeout()) {
                    fsm_timeout();
                    if(order_check_for_order()) {
                        if(fsm_is_order_in_same_floor){
                        //Hvis bestilling i samme etg, åpne dør og slett bestilling
                        order_erase_order(elev_get_floor_sensor_signal());
                        fsm_open_door();
                        current_state = open_door;
                        }
                        else { current_state = moving; }
                    }
                    else { current_state = idle; }
                }
                break;
            }
            case(moving): {
                printf("Moving");
                elev_set_motor_direction(DIRN_UP);


                break;
            }
            case(emergency_stop): {
                fsm_emergency_handler();
                //HVIS I ETASJE, GÅ TIL OPEN DOOR FOR Å LUKKE DØREN
                if(elev_get_floor_sensor_signal()) {
                    current_state = open_door;
                }
                else {
                    //HVIS IKKE I ETASJE, VENT TIL BESTILLING
                    current_state = idle; //OBS: IDLE MIDT I MELLOM TO ETASJER?
                }
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


/*

while(1) {
    switch (state)
    {
        case idle:
            if (order_exist())
                fsm_orderExists()
             code 
            break;
    
        case moving:
            break;
    }


}


fsm_orderExists() 
    
    set_dir
    set motor onorder_same_floor_order
    */
