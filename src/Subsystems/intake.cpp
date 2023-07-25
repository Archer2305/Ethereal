#include "main.h"
#include "intake.hpp"   

okapi::Motor intake(INTAKE_PORT, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

void updateIntake() {
    if (controller.getDigital(BUTTON_INTAKE) == 1) {
        intake.moveVelocity(600); 
    }
    if (controller.getDigital(BUTTON_OUTTAKE) == 1) {
        intake.moveVelocity(-600); 
    }
    if (controller.getDigital(BUTTON_INTAKE) == 0 && (controller.getDigital(BUTTON_OUTTAKE) == 0)){
        intake.moveVelocity(0); 
    }
}
