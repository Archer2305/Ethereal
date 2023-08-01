#ifndef __AUTONFUNC_HPP__
#define __AUTONFUNC_HPP__

#include "drive.hpp"

//-----------------------------------
//remap to -180 to 180
inline double remap(double d) {
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
//------------------------------------

double to_IMU_heading(double heading);

void drive_dis(double, double);
void turnToAngle(double);
void driveToPoint(double, double, double, bool);

void j_curve(double, double, double);
#endif
