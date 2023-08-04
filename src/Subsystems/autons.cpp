#include "autons.hpp"
#include "main.h"

enum {
    NO_AUTON,
    AUTON_LEFT,
    AUTON_RIGHT,
};

int auton_route = AUTON_LEFT;

void leftPressed() {
    auton_route = AUTON_LEFT;
}

void rightPressed() {
    auton_route = AUTON_RIGHT;
}

void autons() {
    printf("-----in autons before 0------\n");
    print_cur_state();
    motors_init();

    odom_set_zero();        //do not delete

    printf("-----in autons-------\n");
    print_cur_state();
    motors_init();

//------------------------------------
    j_curve(2, 4, 1);
//----------------------------------
#if 0
    switch (auton_route) {
        case AUTON_LEFT:
            {
                Drive.moveVelocity(-600);
                pros::delay(5000);
                piston.set_value(1);
                pros::delay(500);
                piston.set_value(0);
                Drive.moveVelocity(25);
                pros::delay(1000);
                Drive.moveVelocity(0);
            }
            break;
        case AUTON_RIGHT:
            {
                drive_dis(1, 0.8);
                turnToAngle(135);
                drive_dis(1,0.8);

                piston.set_value(1);
                drive_dis(-1, 0.8);
                piston.set_value(0);                
            }
            break;
        default:
            break;
    }
#endif
}
