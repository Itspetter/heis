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


//OBS: HER GJØR VI ET VALG OM HVILKEN VEI VI PRIORITERER
//NÅR TO KNAPPER INNE I HEISEN ER TRYKKET.
//BURDE VEL EGENTLIG HA DEN NÆRMESTE ETASJEN? -> get_closest_cab_order
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }     

    //TO DO: LEGGE INN AT KNAPPER I HEISEN HAR HØYEST PRESEDENS


    //I idle etter init
    state current_state = idle;
    elev_motor_direction_t direction;

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
            elev_set_floor_indicator(current_floor);
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
                    else{ 
                        if(order_order_above(last_floor)) {
                            elev_set_motor_direction(DIRN_UP);
                            direction = DIRN_UP;
                        }
                        else if (order_order_below(last_floor)) {
                            elev_set_motor_direction(DIRN_DOWN);
                            direction = DIRN_DOWN;
                        }
                        else if (order_same_floor_order(last_floor)) {
                            if(direction == DIRN_DOWN) {
                                elev_set_motor_direction(DIRN_UP);
                            }
                            else {
                                elev_set_motor_direction(DIRN_DOWN);
                            }
                        }
                        current_state = moving;
                    } 
                }
                //FORSIKRING 
                else {
                    current_state = idle;
                }
                break;
            }
            case(open_door) : {
                order_erase_order(current_floor);
                //HUSK: ANTA AT DØR _ER_ ÅPEN NÅR DU KOMMER HIT!
                //HVIS DØREN SKAL LUKKES
                if(timer_timeout()) {
                    fsm_timeout();
                    if(order_check_for_order()) {
                        if(order_same_floor_order(current_floor)){
                            order_erase_order(current_floor);
                            fsm_open_door();
                            current_state = open_door;
                        }
                        else {
                            elev_motor_direction_t prev_direction = direction;
                            direction = order_get_dir(current_floor, prev_direction);
                            elev_set_motor_direction(direction);
                            current_state = moving; 
                        }
                    }   
                    else {
                        current_state = idle;
                    }
                }
                //FORSIKRING
                else { current_state = open_door; }
                break;
            }
            case(moving) : {
                if(order_same_floor_order(current_floor) && order_is_order_same_dir(current_floor, direction)) {
                    elev_set_motor_direction(DIRN_STOP);
                    fsm_open_door();
                    current_state = open_door; 
                }

                break;
            }
            case(emergency_stop): {
                fsm_emergency_handler();
                //HVIS I ETASJE, GÅ TIL OPEN DOOR FOR Å LUKKE DØREN - VIKTIG"
                
                if(elev_get_floor_sensor_signal() != -1) {
                    printf("Open Door");
                    //fsm_open_door kalles inne i emergency handler
                    current_state = open_door;
                }
                else {
                    printf("Idle");
                    current_state = idle; 
                }
                break;
            }
            default : {
                return 0;
            }
        }

    }

    elev_set_motor_direction(DIRN_STOP);

    return 0;
}

