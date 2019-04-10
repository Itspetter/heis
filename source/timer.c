#include "timer.h"
#include <time.h>


time_t start_time; 

void timer_start(void) {
    start_time = time(NULL);
}

int timer_timeout(void) {
    if(time(NULL) - start_time < 3) {
        return 0; 
    }
    return 1; 
}  

void timer_stop(void){
    start_time = 0;
}