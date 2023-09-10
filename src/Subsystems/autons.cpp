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
    //blocker.set_value(1);
    pros::delay(500);
    intake.moveVelocity(600);
    drive_dis(-1.2, 0.64);
    pros::delay(100);
    drive_dis(3, 0.72);
    intake.moveVelocity(0);
    //blocker.set_value(0);       //integrate into blocker_extend

    //2.3
    j_curve(-2.8, 3.2, false, 1.2);
    //turnToAngle(-105, 1);
    drive_dis(-0.16, 0.88);
    turnToAngle(90, 1);
    intake.moveVelocity(-600);
    pros::delay(500);
    drive_dis(-1, 1);

    
}

void auton_right() {
    
}

void autons() {
    odom_set_zero();        //do not delete
    
    auton_left();
}
