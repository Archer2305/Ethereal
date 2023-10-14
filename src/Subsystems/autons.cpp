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

void auton_test() {
#if 0
    //drive_arc(-1.2, 90, 0.8, true);  //turn around goal

    //drive_dis(2, 0.8);
    for (int i = 0; i < 4; i++) {
        turnToAngle(45 * i);
        pros::delay(280);
    }
    turnToAngle(0);
#endif

    drive_arc(0.5, 90, 0.8, false);
    pros::delay(280);
    drive_arc(0.5, 0, 0.8, true);

    //turnToAngle(90);
    //pros::delay(280);
    //turnToAngle(0);
}

void auton_right() {
#if 0
    turnToAngle(-36);
    intake.moveVelocity(-500);
    drive_dis(-2.4, 1);
    intake.moveVelocity(0);
    drive_arc(2.8, -2, 0.8);

    turnToAngle(-48);
    intake.moveVelocity(-320);
    pros::delay(480)
    intake.moveVelocity(0);
    
    drive_dis(0.8, 0.8);
    turnToAngle(132);
    drive_dis(0.88, 1);
    
    //drive_arc(2.8, 90, 0.8);
    wings.set_state(1);
    pros::delay(640);
    wings.set_state(0);
    turnToAngle(-36);
    drive_dis(2.3, 1);
#endif
    
    turnToAngle(-30, 0.77);
    drive_dis(2.3, 1);
    pros::delay(320);
    drive_dis(-1, 0.8);
    turnToAngle(154, 0.88);
    drive_dis(0.59, 0.88);
    wings.set_state(1);
    pros::delay(320);
    drive_dis(0.5, 1);
    pros::delay(480); 
    turnToAngle(100, 1);
    wings.set_state(0);
    drive_dis(1.82, 0.8);
    turnToAngle(90);
    blocker.set_state(1);
    drive_dis(1.59);
/*
    drive_arc(1.6, -88, 0.88);
    drive_dis(3.2, 0.88);    
 */
}

void auton_n_awp_SV2() {
    intake.moveVelocity(600);
    pros::delay(160);

    drive_dis(-0.32, 0.88);
    pros::delay(320);
    intake.moveVelocity(0); // intake the triball

    drive_dis(1.77, 0.77);
    drive_arc(1.52, -42, 0.88); //1.6
    wings.set_state(1); //toggle the wings 
    pros::delay(160);
    drive_arc(0.5, -90, 0.88);
    wings.set_state(0);
    drive_dis(0.72, 0.8);
    turnToAngle(130, 0.88);
    intake.moveVelocity(-600);
    pros::delay(360);
    turnToAngle(-60);
    intake.moveVelocity(0);
    drive->getModel()->tank(1, 1);
    pros::delay(1200);
    drive->getModel()->tank(0, 0);
    drive_dis(-0.8, 0.8);
}


//working auton, non awp, three triballs, 12 sec
void auton_n_awp_SV1() {
    intake.moveVelocity(600);
    pros::delay(380);

    drive_dis(-0.28, 0.88);
    intake.moveVelocity(0); // inake the triball

    drive_dis(1.82, 0.77);
    intake.moveVelocity(0);
    drive_arc(1.6, -42, 0.8); 
    wings.set_state(1); //toggle the wings 
    pros::delay(450);
    drive_arc(0.5, -90, 0.72);
    pros::delay(200);
    wings.set_state(0);
    turnToAngle(-64);       //-59
    drive_dis(1.4, 1);
    drive_dis(-0.8, 0.8);
    turnToAngle(130, 0.8);
    intake.moveVelocity(-480);
    pros::delay(480);
    drive_dis(0.64, 0.8);
    turnToAngle(-55);
    intake.moveVelocity(0);
    drive->getModel()->tank(1, 1);
    pros::delay(1600);
    drive->getModel()->tank(0, 0);
    drive_dis(-0.8, 0.8);
}

extern okapi::Motor slapper;
void skills() {
    slapper.moveVelocity(600);
    //pros::delay(23000);
    //slapper.moveVelocity(0);
    
}
void autons() {
    odom_set_zero();        //do not delete

    //auton_n_awp_SV2();    
    auton_test();
}   
