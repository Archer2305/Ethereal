#ifndef __AUTONFUNCS_HPP__
#define __AUTONFUNCS_HPP__

using namespace okapi::literals;

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

//inline double reflex_convert(double d) {

//}
//------------------------------------

double to_IMU_heading(double heading);

void drive_dis(double, double);
void turnToAngle(double, double);
void driveToPoint(double, double, double, bool);

void j_curve(double, double, bool, double);
void drive_arc(double, double, double);

#endif
