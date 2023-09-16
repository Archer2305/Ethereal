#include "autons.hpp"
#include "main.h"

enum {
    NO_AUTON,
    AUTON_LEFT,
    AUTON_RIGHT,
};

int auton_route = NO_AUTON;     //change to functional

void leftPressed() {
    auton_route = AUTON_LEFT;
}

void rightPressed() {
    auton_route = AUTON_RIGHT;
}

void auton_left() {
    
}

void auton_right() {
    drive_arc(-3, 30, 0.8);
    pros::delay(100);
    wings.set_state(1);
    drive_arc(-3, 45, 0.8);
}

void auton_test() {
#if 0
    drive_arc(-3, 30, 0.8);
    pros::delay(100);
    wings.set_value(1);
    drive_arc(-3, 45, 0.8);

    //drive_arc(0.5, 90, 0.8);  //point turn
#endif 
}

void autons() {
    odom_set_zero();        //do not delete

    auton_left();    
}
