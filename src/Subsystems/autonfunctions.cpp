#include "main.h"
#include "drive.hpp"
#include "autonfunctions.hpp"

#include <climits>

#define TO_DEG  (180 / 3.14159265359)

okapi::IMU inertial = okapi::IMU(IMU_PORT);

//----------------------------functions---------------------------------------
static double normalize(double d) {      //input[0,360] -> output[-180,180]
    if (d > 180)
        d -= 360;
    return d;
}

static double angle_diff(double d1, double d2) {        //[-180, 180)
    double pd = std::max(d1, d2) - std::min(d1, d2);
    return (pd > 180) ? (360 - pd) : pd;
}
//--------------------------------------

double to_IMU_heading(double d) {
    return normalize(90 - d);
}

void drive_dis(double distance, double scalar=1) {                                          //init 0.85
    if (abs(distance) <= 0.01)
        return;

    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.88, 0.00, 0.0000);
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
                okapi::IterativeControllerFactory::posPID((double)0.01285, 0.0000, 0.0000456);

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
        if (targetAngle >= 0) {
            targetAngle += -180;
        } else if (targetAngle < 0) {
            targetAngle += 180;
        }
    }

    turnToAngle(targetAngle);
    drive_dis((backward ? -1 : 1) * distance, speed);
}

static double cal_t_angle(double tx, double ty) {
    double dx = tx - drive->getState().x.convert(okapi::foot);
    double dy = ty - drive->getState().y.convert(okapi::foot);

    if (!dx && !dy) {
        return 0;
    }

    double target_angle = 0;

    if (dx == 0) {
        target_angle = (dy > 0) ? 90 : -90;
    } else if (dx > 0) {
        target_angle = atan(dy/dx) * TO_DEG;
    } else if (dx < 0) {
        target_angle = 180 + (atan(dy/dx)) * TO_DEG;
    }

    target_angle = to_IMU_heading(normalize(target_angle));

    return target_angle;
}

//note: reverse all coordinate pairs
void j_curve(double tx, double ty, double turn_scalar=1) {
    okapi::IterativePosPIDController forwardPID =
                okapi::IterativeControllerFactory::posPID(0.888, 0, 0);
    okapi::IterativePosPIDController turnPID =
                okapi::IterativeControllerFactory::posPID(0.0128, 0, 0.0000456); //0.0128

    double ix = drive->getState().y.convert(okapi::foot);
    double iy = drive->getState().x.convert(okapi::foot);

    printf("-------------ix: %lf, iy: %lf---------------\n", ix, iy);

    double dx = tx  + 0 - ix;
    double dy = ty - iy;

    double d_dis = sqrt(dx * dx + dy * dy);     //dx and dy used once
    forwardPID.setTarget(d_dis);

    //turnPID.setTarget(cal_t_angle(tx, ty));

    int ta_reached = 0;
    double dvn_dis = 0;

    while (abs(d_dis - dvn_dis) >= 0.5 || std::max(abs(leftDrive.getActualVelocity()), abs(rightDrive.getActualVelocity())) > 10) {
    //while (true) { 
        double cx = drive->getState().y.convert(okapi::foot);
        double cy = drive->getState().x.convert(okapi::foot);
        double dvn_x = cx - ix;
        double dvn_y = cy - iy;
        dvn_dis = sqrt(dvn_x * dvn_x + dvn_y * dvn_y);

        double fs = forwardPID.step(dvn_dis);

        double ta = cal_t_angle(tx, ty);
        double ca = inertial.controllerGet();
        double ts;
/*
        if (angle_diff(ta, ca) < 1) {
            ta_reached = 1;
            turnPID.reset();
        }
*/
        //if (ta_reached) {
            //ts = 0;
        //} else {
            turnPID.setTarget(ta);     //recalc
            ts = turnPID.step(ca) * turn_scalar;
        //}

        printf("drvn dis: %lf, target angle: %lf, ca: %lf, ta_reached: %d, Forward_S: %lf, Turn_S: %lf, cur_ang_diff: %lf\n"
                , dvn_dis, ta, ca, ta_reached, fs, ts, angle_diff(ta, ca));
        //printf("drvn dis: %lf, target angle: %lf, dvn_x: %lf, dvn_y: %lf , cx: %lf, cy: %lf, cur_ang_diff: %lf\n", 
                //dvn_dis, ta, dvn_x, dvn_y, cx, cy, angle_diff(ta, ca));
        
        double left_spd = (fs + ts) * 0.5;
        double right_spd = (fs - ts) * 0.5;
        
        printf("left spd: %lf, right spd:%lf\n", left_spd, right_spd);

        drive->getModel()->tank(left_spd, right_spd);
        pros::delay(20);
   }

    turnPID.reset();
    forwardPID.reset();
    drive->getModel()->tank(0, 0);

    pros::delay(8);
}


#if 0
// r < 0 (left), r > 0 (right)
double drive_arc(double r, double theta, double scalar=0.8) {     //returns distance
    double sd = abs(r) - (DRIVE_WIDTH / 2);
    double ld = abs(r) + (DRIVE_WIDTH / 2);

    if (r > 0)
}
#endif
