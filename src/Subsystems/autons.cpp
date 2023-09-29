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

    drive_dis(2, 1);
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

    intake.moveVelocity(500);
    drive_dis(-0.28, 0.8);
    pros::delay(230);
    intake.moveVelocity(0);

    drive_dis(1.45, 0.88);
    drive_arc(1.8, -45, 1); 
    wings.set_state(1);
    pros::delay(480);
    drive_arc(0.5, -77, 0.8);
    wings.set_state(0);
    drive_arc(0.8, -90, 1);

    pros::delay(20);
    turnToAngle(-50); //turn towards goal
    drive_dis(1.5); //score two triballs

    pros::delay(50);
    drive_dis(-1.2);
    turnToAngle(8); 

    printf("------------!!!---------\n");
    drive_arc(-1.2, 90, 0.8, true);  //turn around goal
    printf("------------------------\n");
    pros::delay(320);
    intake.moveVelocity(-320);  //spit out triball
    pros::delay(230);
    drive_dis(0.8, 0.88);
    intake.moveVelocity(0);
    
    turnToAngle(22);    //go towards second triball
    intake.moveVelocity(600);
    drive_dis(-1.89, 0.88);
    pros::delay(280);
    intake.moveVelocity(0);
    wings.set_state(1);

    drive_arc(0.64, 135, 0.8, true);
    
    // drive_arc(-2, -60, 0.8);

    // wings.set_state(1);
}

void autons() {
    odom_set_zero();        //do not delete

    auton_left();    
}   
