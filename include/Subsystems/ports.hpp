#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     18
#define RIGHT_MIDDLE    12
#define RIGHT_BACK      11

#define LEFT_FRONT      17
#define LEFT_MIDDLE      4
#define LEFT_BACK        2
//-------------------------

//----------intake----------
#define INTAKE_PORT     10
//--------------------------

//----------slapper----------
#define SLAPPER_PORT     15
//--------------------------

//---------sensors----------
#define IMU_PORT        16
//--------------------------

//----------------------buttons-------------------------------
#define BUTTON_INTAKE           okapi::ControllerDigital::R1
#define BUTTON_OUTTAKE          okapi::ControllerDigital::L1

#define AUTON_M_ACTUATE         okapi::ControllerDigital::L2

#define BUTTON_SLAPPER          okapi::ControllerDigital::R2
#define BUTTON_SLAPPER_REV      okapi::ControllerDigital::B
//-----------------------------------------------------------

#endif 
