#include "main.h"
#if 0
pros::ADIDigitalOut wings('A');

static int last_input = 0;
static int piston_state = 0;

void update_wings() {
    int input = controller.getDigital(WINGS_ACTUATE); 

    if (input && !last_input) {
        if (!piston_state) {
            wings.set_value(1);
            piston_state = 1;
        } else {
            wings.set_value(0);
            piston_state = 0;
        }
    }

    last_input = input;
}
#endif   
