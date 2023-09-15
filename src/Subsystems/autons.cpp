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
#if 0
    //blocker.set_value(1);
    //pros::delay(500);
    intake.moveVelocity(600);
    drive_dis(-0.64, 0.64);
    pros::delay(200);
    drive_dis(2.56, 0.72);
    intake.moveVelocity(0);
    //blocker.set_value(0);       //integrate into blocker_extend

    //2.3
    j_curve(-2.8, 2.8, false, 0.84);
    //turnToAngle(-105, 1);
    turnToAngle(-90, 1);
    //drive_dis(-0.28, 0.8);
    //turnToAngle(90, 1);
    //intake.moveVelocity(-600);
    //pros::delay(640);
    drive_dis(-0.48, 1);
    drive_dis(0.8, 1);

    drive_dis(-1.6, 0.88);
    turnToAngle(30, 0.95);
    drive_dis(-3, 0.88);
    turnToAngle(90, 0.8);
    drive_dis(-2, 0.8);
    intake.moveVelocity(600);
    pros::delay(160);
    
    
    intake.moveVelocity(0);

    blocker.set_value(1);
    intake.moveVelocity(600);
    drive_dis(0.28, 0.72);
    pros::delay(230);
    blocker.set_value(0);

    intake.moveVelocity(0);
    drive_dis(3.65, 0.72);
    turnToAngle(90, 0.88);
    wings.set_value(1);
    pros::delay(230);
    drive_dis(1.8, 1);
    
    intake.moveVelocity(-600);
    pros::delay(230);
    drive_dis(-2.5, 1);
    intake.moveVelocity(0);
    wings.set_value(0);
    
    drive_dis(-1.6, 1);
#endif

}

void auton_right() {
    blocker.set_value(1);
    pros::delay(230);
    blocker.set_value(0);
    
    drive_dis(-3.33, 0.88);
    intake.moveVelocity(0);
    turnToAngle(90, 0.88);
    
    intake.moveVelocity(-600);
    //drive_dis(-0.8, 1);
    pros::delay(640);

    //intake.moveVelocity(0);
    drive_dis(0.88, 0.88);
    turnToAngle(-48, 0.88);
    drive_dis(-1.25, 0.88);
    intake.moveVelocity(600);
    drive_dis(-0.4, 1);
    pros::delay(160);
    intake.moveVelocity(0);
    wings.set_value(1);
    drive_dis(0.88, 0.8);
    turnToAngle(-93, 0.72);
    drive_dis(2.3, 0.88);
    
    

    intake.moveVelocity(0);
    
}

void auton_one() {
    drive_arc(-3, 30, 0.8);
    pros::delay(100);
    wings.set_value(1);
    drive_arc(-3, 45, 0.8);
}

void autons() {
    odom_set_zero();        //do not delete
    
    auton_one();
}
