#include "timer.h"
#include <time.h>


struct timeStruct {
    time_t timestamp;
};


static struct timeStruct start_time;


void timer_start() {
    start_time.timestamp = time(NULL);
}

int timer_timeout(void) {
    if(time(NULL) - start_time.timestamp < 3) {
        return 0; 
    }
    return 1; 
}  

void timer_stop(void){
    start_time.timestamp = 0;
}