#include "autons.hpp"
#include "main.h"

enum {
    NO_AUTON,
    AUTON_LEFT,
    AUTON_RIGHT,
};

int auton_route = NO_AUTON;

void leftPressed() {
    auton_route = AUTON_LEFT;
}

void rightPressed() {
    auton_route = AUTON_RIGHT;
}

void autons() {
    switch (auton_route) {
        case AUTON_LEFT:
            {
                drive_dis(1, 0.8);
                turnToAngle(-135);
                drive_dis(1,0.8);

                piston.set_value(1);
                drive_dis(-1, 0.8);
                piston.set_value(0);
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
}