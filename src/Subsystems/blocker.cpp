#include "main.h"

pros::ADIDigitalOut blocker('H');

static int last_input = 0;
static int piston_state = 0;

void update_blocker() {
    int input = controller.getDigital(BLOCKER_ACTUATE); 

    if (input && !last_input) {
        if (!piston_state) {
            blocker.set_value(1);
            piston_state = 1;
        } else {
            blocker.set_value(0);
            piston_state = 0;
        }
    }

    last_input = input;
}
    
        
