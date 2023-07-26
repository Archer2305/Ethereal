#include "main.h"

pros::ADIDigitalOut piston('B');

static int last_input = 0;
static int piston_state = 0;

void update_auton_mech() {
    int input = controller.getDigital(AUTON_M_ACTUATE); 

    pros::lcd::set_text(3, std::to_string(piston_state));
    pros::lcd::set_text(4, std::to_string(last_input));
    pros::lcd::set_text(5, std::to_string(input));

    if (input && !last_input) {
        if (!piston_state) {
            piston.set_value(1);
            piston_state = 1;
        } else {
            piston.set_value(0);
            piston_state = 0;
        }
    }

    last_input = input;
}
    
        
