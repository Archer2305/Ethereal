#ifndef __DRIVE_HPP__
#define __DRIVE_HPP__

extern okapi::MotorGroup leftDrive;
extern okapi::MotorGroup rightDrive;
extern okapi::MotorGroup Drive;

extern std::shared_ptr<okapi::OdomChassisController> drive;

//-------------------------------------------------
void print_state(std::string, const okapi::OdomState&);
void print_cur_state();

void updateDrive();

#endif
