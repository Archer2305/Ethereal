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
    turnToAngle(103, 1);
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

//---------------------------------work-------------------------------------
//turn scalar to not exceed 0.90, drive and arc scalar not to exceed 0.935
//standards: 0.64, 0.72, 0.77, 0.8, 0.88, 0.90, 0.935
//make sure air is pumped
void auton_n_awp_SV2() {
    intake.moveVelocity(600);
    //pros::delay(80);

    drive_dis(-0.32, 0.88);
    //pros::delay(80);      //tbr
    intake.moveVelocity(0);         //intake the triball

    drive_dis(1.78, 0.80, false);          //1.72 wk 
    drive_arc(1.52, -42, 0.936);    //1.52
    wings.set_state(1);             //toggle the wings 
    drive_arc(0.5, -90, 0.9365);      //-93
    turnToAngle(-65, 0.90);
    wings.set_state(0);
    pros::delay(80);        //wait for wings
    drive_dis(1.72, 1);
    drive_dis(-0.8, 0.88);
    turnToAngle(120, 0.88);
    intake.moveVelocity(-600);      //outtake elevation triball
    drive_dis(0.32, 0.64);          //step back
    drive->getModel()->tank(-0.88, -0.88);
    pros::delay(420);
    intake.moveVelocity(0);
    drive->getModel()->tank(0, 0);
    drive_dis(1.28, 0.88);         //~8.5 sec     //-1.75

    turnToAngle(26, 0.90);          //p2
    intake.moveVelocity(600);
    drive_dis(-3.75, 0.88);         //-4.2
//drive_arc
    pros::delay(230);               //rd
    drive_dis(0.5, 0.88);

    intake.moveVelocity(0);
    turnToAngle(-88, 0.88);          //p2
    drive_dis(1.42, 1);              //2.3
    pros::delay(230);               //rd
    wings.set_state(1);
    drive_arc(0.8, 0, 1);
    drive_dis(1, 1);
    //drive_arc(0.8, 0, 0.936);
    drive_dis(-1, 1);
#if 0
    turnToAngle(180, 0.90);
    intake.moveVelocity(-600);
    drive->getModel()->tank(-1, -1);
    pros::delay(640);
    intake.moveVelocity(0);
    drive->getModel()->tank(0.8, 0.8);
    //run intake
#endif
}

void auton_n_awp_SV3() {
    intake.moveVelocity(600);
    //pros::delay(80);

    drive_dis(-0.32, 0.88);
    //pros::delay(80);      //tbr
    intake.moveVelocity(0);         //intake the triball

    drive_dis(1.78, 0.80, false);          //1.72 wk 
    drive_arc(1.52, -42, 0.936);    //1.52
    wings.set_state(1);             //toggle the wings 
    drive_arc(0.5, -90, 0.9365);      //-93
    turnToAngle(-65, 0.90);
    wings.set_state(0);
    pros::delay(80);        //wait for wings
    drive_dis(1.72, 1);
    drive_dis(-0.8, 0.88);
    turnToAngle(120, 0.88);
    intake.moveVelocity(-600);      //outtake elevation triball
    drive_dis(0.32, 0.64);          //step back
    drive->getModel()->tank(-0.88, -0.88);
    pros::delay(420);
    intake.moveVelocity(0);
    drive->getModel()->tank(0, 0);
    drive_dis(1.28, 0.88);         //~8.5 sec     //-1.75

    turnToAngle(26, 0.90);          //p2
    intake.moveVelocity(600);
    drive_dis(-3.75, 0.88);         //-4.2
//drive_arc
    pros::delay(230);               //rd

    intake.moveVelocity(0);
    turnToAngle(-92, 0.88);          //p2           //-90b
    drive_dis(1.72, 1);              //2.3
    turnToAngle(180, 0.88);          //p2
    intake.moveVelocity(-600);
    drive_dis(-2, 1);
    drive_dis(1, 0.8);
}
//------------------------------------------------------------------------

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
    turnToAngle(20);
    drive->getModel()->tank(-0.05, 0);
    slapper.moveVelocity(600);
    //pros::delay(25000);
    slapper.moveVelocity(0);
    drive->getModel()->tank(0, 0);
    drive_dis(0.3, 1);
    turnToAngle(-15);
    drive_dis(2, 1);
    turnToAngle(0);
    drive_dis(4, 1);
    wings.set_state(1);
    drive_arc(2.3, 60);
    wings.set_state(0);
    drive->getModel()->tank(1, 1);
    

    //pros::delay(23000);
    //slapper.moveVelocity(0);
    
}

void autons() {
    odom_set_zero();        //do not delete

    skills();
    //auton_right();    
    //auton_test();
}   
