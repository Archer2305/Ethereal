#ifndef __DRIVE_HPP__
#define __DRIVE_HPP__

#define WHEEL_SIZE      4.125_in
#define DRIVE_WIDTH     13_in
#define GEAR_RATIO      ((double)2. / 1.)

#define DRIVE_H_WIDTH     6.5

extern okapi::MotorGroup leftDrive;
extern okapi::MotorGroup rightDrive;
extern okapi::MotorGroup Drive;

extern std::shared_ptr<okapi::OdomChassisController> drive;

//-------------------------------------------------
void print_state(std::string, const okapi::OdomState&);
void print_cur_state();
void motors_init();
void odom_set_zero();

void updateDrive();

#endif
