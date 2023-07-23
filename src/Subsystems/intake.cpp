#include "main.h"
#include "intake.hpp"   
#include <list>
#include <mutex>

#define BUTTON_RESET        -1
#define BUTTON_INTAKE       okapi::ControllerDigital::L1   //mv to globals
#define BUTTON_OUTTAKE       okapi::ControllerDigital::R1

okapi::Motor intake(INTAKE_PORT, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

//static volatile std::atomic<int> intake_state = INTAKE_STANDBY;                 //uhh state machine
volatile bool triball_detected = false;                         //for other version

static std::atomic<long> avg_intake_watt = -1;                                   //*10, experimental value, testing only
constexpr double mean_intake_watt = -1;

void updateIntake() {       //testing
    printf("motor efficiency: %lf, motor wattage: %lf, motor voltage: %ld\n", 
            intake.getEfficiency(), intake.getPower(), intake.getVoltage());
    
    if (controller.getDigital(BUTTON_INTAKE) == 1) {
        intake.moveVelocity(-600); 
    }
    if (controller.getDigital(BUTTON_INTAKE) == 1) {
        intake.moveVelocity(600); 
    }
    if (controller.getDigital(BUTTON_INTAKE) == 0 && (controller.getDigital(BUTTON_OUTTAKE) == 0)){
        intake.moveVelocity(0); 
    }
}


#if 0 
enum {              //intake states
    INTAKE_STANDBY = 0,
    INTAKE_ACTIVE,
    OUTTAKE_STANDBY,
    OUTTAKE_ACTIVE
};

enum {              //messages
    TRIGGER_RESET,
    TRIGGER_INTAKE,
    TRIGGER_OUTTAKE
};   

static std::list<int> intake_messages;
static std::atomic<int> intake_messages_count;


void append_message(int button_message) {                    //appends to message box
     
}


void updateIntake_button_dispatch() {       //checks buttons, called repeatedly in opcontrol
    static int last_reset = 0;
    static int last_intake = 0;
    static int last_outtake = 0;

    int cur_reset = controller.getDigital(BUTTON_RESET);
    int cur_intake = controller.getDigital(BUTTON_INTAKE);
    int cur_outtake = controller.getDigital(BUTTON_OUTTAKE);

    if (!last_reset && cur_reset) 
        append_message(TRIGGER_RESET);
    if (!last_intake && cur_intake) 
        append_message(TRIGGER_INTAKE);
    if (!last_outtake && cur_outtake) 
        append_message(TRIGGER_OUTTAKE);
    
    last_reset = cur_reset;
    last_intake = cur_intake;
    last_outtake = cur_outtake;
}

//to abort ongoing intake, (reset) + outtake button |or| reset function to include outtake 
//to reset inaccurate robot state due to improper intake, press reset to INTAKE_STANDBY
//to abort ongoing outtake, (reset) + intake trigger

void update_intake() {} //motor + state machine

//less complicated version embedded in opcontrol, intake would stop while it has a triball, outtake works normally 
void updateIntake_manual_op() {
    //read buttons
    //check intake is true
    //
}


#if 0
void set_dir_intake() {}                //static
void set_dir_outtake() {}

void intake_until_ingested() {}          //async

void outtake_until_empty() {}            //async

void updateIntake_manualOp() {         // emergency manual op

}

int updateIntake_button_dispatch() { 

void updateIntake() {                   //threaded
    //if(button pressed out) 
        //set_intake dir out + active
    //if (button pressed in 
        //set_intake dir in + active    
} 
#endif
#endif
