#include "elev.h"
#include "order.h"
#include "fsm.h"
#include "timer.h"
#include <stdio.h>




int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }     

    fsm_fsm();

    return 0;
}

