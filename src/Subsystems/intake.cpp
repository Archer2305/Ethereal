#include "main.h"
#include "intake.hpp"   //move to main.h

#define INTAKE_PORT     -1          //move ports into ports file

okapi::Motor intake(INTAKE_PORT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
 
enum {
    INTAKE_STANDBY = 0,
    INTAKE_ACTIVE,
    OUTTAKE_STANDBY,
    OUTTAKE_ACTIVE
};

static volatile std::atomic<int> intake_state = INTAKE_STANDBY;                  //uhh state machine
static std::atomic<int> avg_intake_watt = -1;                        //*10, fill experimental avg value

void set_dir_intake() {}
void set_dir_outtake() {}

void intake_until_ingested() {          //async

}

void outtake_until_empty() {            //async

}

void updateIntake_manual() {            //async
    
}

void updateIntake() {                   //threaded
     //intake direction based on state 
} 
