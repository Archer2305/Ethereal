#include "main.h"
#include "slapper.hpp"

okapi::Motor slapper(SLAPPER_PORT, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

void updateSlapper() {
    if (controller.getDigital(BUTTON_SLAPPER) == 1) {
        slapper.moveVoltage(12000); 
    }
//    if (controller.getDigital(BUTTON_SLAPPER_REV) == 1) {
//        intake.moveVoltage(-12000); 
//    }
    if (controller.getDigital(BUTTON_SLAPPER) == 0){
        slapper.moveVoltage(0); 
    }
}