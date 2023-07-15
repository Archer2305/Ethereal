#include "main.h"
#include "drive.hpp"

#define TO_DEG  (180 / 3.14159265359)

okapi::IMU inertial = IMU(-1);

//----------------------------functions---------------------------

//remap to -180 to 180
static inline double remap(double d) {
    if (d == 0) {
        return 0;
    }

    double fp = d - (int)d;
    int id = (int)d;

    if (d > 0) {
        id = id % 360;
    } else {
        id = (-id % 360) * -1 + 360;
    }

    d = id + fp;
    return (d <= 180) ? d : (d - 360);
}

static inline double normalize(double d) {      //input[0,360] -> output[-180,180]
    if (d > 180)
        d -= 360;
    return d;
}

//------------

inline double to_IMU_heading(double d) {
    return normalize(90 - d);
}

void drive_dis(double distance, double scalar=1) {                                          //init 0.85
    if (abs(distance) <= 0.01)
        return;

    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.86, 0.00, 0.0000);
    //okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.75, 0.01, 0.01); 

    double target = distance;

    drivePID.setTarget(target);

    double orgPosX = drive->getState().x.convert(okapi::foot);
    double orgPosY = drive->getState().y.convert(okapi::foot);
    printf("\n-->  start    => %10.3lf    : state = (%9.5lf, %9.5lf)\n", distance, orgPosX, orgPosY);

    double distTravelled = 0;

    while (abs(target-distTravelled) >= 0.2 || abs(leftDrive.getActualVelocity()) > 10) { 
     // while (true) {                  //tuning
        double state_x = drive->getState().x.convert(okapi::foot);
        double state_y = drive->getState().y.convert(okapi::foot);

        double dx = state_x - orgPosX;
        double dy = state_y - orgPosY;

        distTravelled = sqrt(dx * dx + dy * dy);

        if (distance < 0)
            distTravelled = -distTravelled;
        printf("     %10.3lf  => %10.3lf    : state = (%10.3lf, %10.3lf)\n", distTravelled, distance, state_x, state_y);

        double vel = drivePID.step(distTravelled);

        //printf("distTravelled: %lf, cur_x: %lf, cur_y:%lf\n",
        //   distTravelled, drive->getState().y.convert(okapi::foot), drive->getState().x.convert(okapi::foot));

        drive->getModel()->tank(vel * scalar, vel * scalar);
        pros::delay(16);
    }

    double state_x = drive->getState().x.convert(okapi::foot);
    double state_y = drive->getState().y.convert(okapi::foot);
    printf("-->   end      : state = (%10.3lf, %10.3lf)\n", state_x, state_y);

    drivePID.reset(); 
    drive->getModel()->tank(0, 0); 
}

void turnToAngle(double targetAngle) {
    okapi::IterativePosPIDController rotatePID = 
                okapi::IterativeControllerFactory::posPID((double)0.027, 0.00001, 0.00070);

    rotatePID.setTarget(0);

    double initAngle = remap(inertial.controllerGet() - targetAngle);

    while (abs(0 - initAngle) >= 3 || abs(leftDrive.getActualVelocity()) > 15) {
    //while (true) {                //tuning
        initAngle = remap(inertial.controllerGet() - targetAngle);

        if (initAngle >= 190) {
            printf("uhhhhh this went bad\n");
            break;
        }

        double vel = rotatePID.step(initAngle);
        drive->getModel()->tank(vel, -vel);

        pros::delay(20);
    }

    rotatePID.reset();
    drive->getModel()->tank(0, 0);

    printf("IMU: %lf\n", inertial.controllerGet());
}

void driveToPoint(double posX, double posY, double speed=0.8, bool backward=false) {
    double ogXPos = drive->getState().y.convert(okapi::foot); 
    double ogYPos = drive->getState().x.convert(okapi::foot);

    double distance = sqrt(pow((posX - ogXPos), 2) + pow((posY - ogYPos), 2));

    double targetAngle = 0;

    //----------------n_algo-----------
    double dx = posX - ogXPos;
    double dy = posY - ogYPos;

    printf("distance: %lf, dX: %lf, dY: %lf\n", distance, dx, dy);

    if (!dx && !dy) {
        return;
    }

    if (dx == 0) {
        targetAngle = (dy > 0) ? 90 : -90;
    } else if (dx > 0) {
        targetAngle = atan(dy/dx) * TO_DEG;
    } else if (dx < 0) {
        targetAngle = 180 + (atan(dy/dx)) * TO_DEG;
    }

    //normalizing + IMU convert
    targetAngle = to_IMU_heading(normalize(targetAngle));

    if (backward) {                    //If driving intake backward 
        if (targetAngle >= 0){
            targetAngle += -180;
        } else if (targetAngle < 0){
            targetAngle += 180;
        }
    }

    turnToAngle(targetAngle);
    drive_dis((backward ? -1 : 1) * distance, speed);
}
