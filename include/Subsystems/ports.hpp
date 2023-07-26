#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     -1
#define RIGHT_MIDDLE    -1
#define RIGHT_BACK      -1

#define LEFT_FRONT      -1
#define LEFT_MIDDLE     -1
#define LEFT_BACK       -1
//-------------------------

//----------intake----------
#define INTAKE_PORT     10
//--------------------------

//---------sensors----------
#define IMU_PORT        16
//--------------------------

//---------buttons--------------------------------------
#define BUTTON_INTAKE       okapi::ControllerDigital::L1
#define BUTTON_OUTTAKE      okapi::ControllerDigital::L2

#define AUTON_M_ACTUATE     okapi::ControllerDigital::A
//-------------------------------------------------------

#endif 
