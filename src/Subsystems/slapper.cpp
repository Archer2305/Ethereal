#include "main.h"
#include "slapper.hpp"

okapi::Motor slapper(SLAPPER_PORT, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

#if 0
static int last_input;
static int slapper_state = 0;

void updateSlapper() {
    slapper.setBrakeMode(okapi::AbstractMotor::brakeMode::hold); 
    int input = controller.getDigital(BUTTON_SLAPPER);

    pros::lcd::set_text(4, std::to_string(slapper.getEfficiency()));

    if (input && !last_input) {
        if (!slapper_state) {
            slapper.moveVelocity(75);
            slapper_state = 1;
        } else {
            slapper.moveVelocity(0);
            slapper_state = 0;
        }
    }

    last_input = input;
}
#endif 

void reset_cata() {
    printf("reset start\n");
    slapper.moveVelocity(75);
    while (slapper.getEfficiency() > 64) {
        pros::delay(28);
    }
    pros::delay(120);
    slapper.moveVelocity(0);
    printf("reset end\n");
}

void updateSlapper() {
    slapper.setBrakeMode(okapi::AbstractMotor::brakeMode::hold); 
    
    pros::lcd::set_text(4, std::to_string(slapper.getEfficiency()));
    
    if (controller.getDigital(BUTTON_SLAPPER) == 1) {
        slapper.moveVoltage(12000); 
    } else if (controller.getDigital(okapi::ControllerDigital::Y) == 0){
        slapper.moveVoltage(0); 
    }
}
