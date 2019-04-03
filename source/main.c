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


//TEST VI KAN KJØRE PÅ MANDAG: HA HEISEN I ETASJE. TRYKK PÅ KNAPP I SAMME ETASJE. SE OM DØREN ÅPNER SEG. TRYKK DERETTER PÅ ANNEN ETASJE. SE OM DEN KJØRER OPPOVER

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }     

    //FUNKER PR 01.04: Init går veldig fint. Knapper nullstilles.
    //Timer funker fint!
    //Trykker i samme etasje -> døren åpner fint!
    //Trykker i annen etasje -> går til moving!
    //Emergency funker både i etasje og i bevegelse

    //TO DO: MOVING! og fikse på hva som skal kalles fsm
    
    //I idle etter init
    state current_state = idle;
    
    while (1) {
        //Sjekk på stoppknapp for hver iterasjon
        if(elev_get_stop_signal()) {
            current_state = emergency_stop;
        }
        
        //Legg inn bestilling hvis en eller flere knapper trykkes
        fsm_check_buttons_place_order();
        
        //MINNE FOR Å HUSKE SIST ETASJE NÅR VI ER I BEVEGELSE
        int current_floor = elev_get_floor_sensor_signal();
        int last_floor; 
        if(current_floor != -1) {
            last_floor = current_floor;
        }
        
        
        switch(current_state) {
            case(idle): {
                //
                if(order_check_for_order()){
                    if(order_same_floor_order(current_floor)){
                        //Hvis bestilling i samme etg, åpne dør og slett bestilling
                        fsm_open_door();
                        order_erase_order(current_floor);
                        current_state = open_door;
                    }

                    else{ current_state = moving;} 
                }
                //FORSIKRING (EVT UNDERSTREKING)
                else {
                    current_state = idle;
                }
                break;
            }
            case(open_door) : {
                //HUSK: ANTA AT DØR _ER_ ÅPEN NÅR DU KOMMER HIT!
                //HVIS DØREN SKAL LUKKES
                if(timer_timeout()) {
                    fsm_timeout();
                    order_erase_order(current_floor);
                    if(order_check_for_order()) {
                        if(order_same_floor_order(current_floor)){
                        //Hvis bestilling i samme etg, åpne dør og slett bestilling
                            order_erase_order(current_floor);
                            fsm_open_door();
                            current_state = open_door;
                            printf("Open Door");
                        }
                        //Ellers: bestilling i annen etasje
                        else {
                            printf("Moving");
                            
                            current_state = moving; 
                        }
                    }   
                    else {
                        printf("Idle");
                        current_state = idle;
                    }
                }
                //FORSIKRING
                else { current_state = open_door; }
                break;
            }
            case(moving) : {
                //fsm_moving_up();
                if(order_same_floor_order(current_floor)) {
                    elev_set_motor_direction(DIRN_STOP);
                    fsm_open_door();
                    current_state = open_door; 
                }
                else if(order_order_above(last_floor)) {
                    elev_set_motor_direction(DIRN_UP);
                 }
                else if (order_order_below(last_floor)){
                     elev_set_motor_direction(DIRN_DOWN);
                }
                
                break;
            }
            case(emergency_stop): {
                fsm_emergency_handler();
                //HVIS I ETASJE, GÅ TIL OPEN DOOR FOR Å LUKKE DØREN - VIKTIG"
                
                if(elev_get_floor_sensor_signal() != -1) {
                    printf("Open Door");
                    current_state = open_door;
                }
                else {
                    //HVIS IKKE I ETASJE, VENT TIL BESTILLING
                    //SPØR OM DETTE
                    printf("Idle");
                    current_state = idle; //OBS: IDLE MIDT I MELLOM TO ETASJER?
                }
                break;
            }
            default : {
                return 0;
            }
        }
        
        // Change direction when we reach top/bottom floor
        /*if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_STOP);
            current_state = idle; 
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }*/

    }
    elev_set_motor_direction(DIRN_STOP);

    return 0;
}

