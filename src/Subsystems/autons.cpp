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
    drive_dis(1);    
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
#endif 
    
    intake.moveVelocity(600);
    drive_dis(-0.28, 0.8);
    pros::delay(280);
    intake.moveVelocity(0);
    drive_dis(0.28, 0.8);

    drive_dis(1.2, 1);
    drive_arc(1.8, -45, 1); 
    wings.set_state(1);
    pros::delay(480);
    drive_arc(0.5, -77, 0.8);
    wings.set_state(0);
    drive_arc(0.8, -90, 0.8);
}

void autons() {
    odom_set_zero();        //do not delete

    auton_test();    
}
