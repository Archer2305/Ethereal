#include "main.h"
#include "slapper.hpp"

okapi::Motor slapper(SLAPPER_PORT, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

void updateSlapper() {
    slapper.setBrakeMode(okapi::AbstractMotor::brakeMode::hold); 
    
    if (controller.getDigital(BUTTON_SLAPPER) == 1) {
        slapper.moveVoltage(12000); 
    } else if (controller.getDigital(okapi::ControllerDigital::Y) == 0){
        slapper.moveVoltage(0); 
    }
}
