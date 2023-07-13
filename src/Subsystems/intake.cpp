#include "intake.hpp"

okapi::motor intake(0, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
 
enum {
    INTAKE_STOP = 0,
    INTAKE_SPINNING,
    OUTTAKE_STOP,
    OUTTAKE_SPINNING
};

static volatile atomic_int intake_state = INTAKE_STOP;                  //uhh state machine
static atomic_int avg_intake_watt = -1;                        //*10, fill experimental avg value

bool set_dir_intake() {}
bool set_dir_outtake() {}

void intake_until_ingested() {          //async

}

void outtake_until_empty() {            //async

}

void updateIntake_manual() {            //async
    
}

void updateIntake() {                   //threaded
     //intake direction based on state 
} 
