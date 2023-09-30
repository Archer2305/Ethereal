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
    //drive_arc(-1.2, 90, 0.8, true);  //turn around goal

    //drive_dis(2, 1);
     turnToAngle(45);
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
    pros::delay(380);

    drive_dis(-0.28, 0.88);
    intake.moveVelocity(0); // inake the triball

    drive_dis(1.52, 1);
    intake.moveVelocity(0);
    drive_arc(1.6, -45, 0.95); 
    wings.set_state(1);//toggle the wings 
    pros::delay(450);
    drive_arc(0.5, -90, 0.8);
    printf("DEBUG: DRIVE ARC EXITED\n");
    pros::delay(200);
    wings.set_state(0);
    printf("turn start\n");
    turnToAngle(-75);
    printf("turn end\n");
    drive_dis(1.7);
    // drive_arc(0.5, -85, 0.95);
    // pros::delay(530);
    // turnToAngle(-77, 1);
    // wings.set_state(0);
/*
    pros::delay(20);
    turnToAngle(-50); //turn towards goal
    drive_dis(1, 1); //score two triballs   1.32

    pros::delay(50);
    drive_dis(-1.2);
    turnToAngle(8); 

    printf("------------!!!---------\n");
    drive_arc(-1.2, 90, 0.8, true);  //turn around goal
    printf("------------------------\n");
    pros::delay(320);
    intake.moveVelocity(-240);  //spit out triball
    pros::delay(250);
    drive_dis(0.8, 0.88);
    intake.moveVelocity(0);

    turnToAngle(20);    //go towards second triball
    intake.moveVelocity(600);
    drive_dis(-1.62, 0.88);
    pros::delay(280);
    intake.moveVelocity(0);

    drive_dis(1, 0.8);
    turnToAngle(-90, 0.8);
    wings.set_state(1);
    drive_arc(1.52, -8, 0.8, true);
*/
}

void autons() {
    odom_set_zero();        //do not delete

    auton_test();    
}   
