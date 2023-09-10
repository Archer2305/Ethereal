#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     1
#define RIGHT_MIDDLE    5
#define RIGHT_BACK      10

#define LEFT_FRONT      11
#define LEFT_MIDDLE     15
#define LEFT_BACK       19
//-------------------------

//----------intake----------
#define INTAKE_PORT     16
//--------------------------

//----------slapper----------
#define SLAPPER_PORT     4
//--------------------------

//---------sensors----------
#define IMU_PORT        12
//--------------------------

//----------------------buttons-------------------------------
#define BUTTON_INTAKE           okapi::ControllerDigital::R1
#define BUTTON_OUTTAKE          okapi::ControllerDigital::R2

#define AUTON_M_ACTUATE         okapi::ControllerDigital::L2
#define WINGS_ACTUATE           okapi::ControllerDigital::L1
#define BLOCKER_ACTUATE         okapi::ControllerDigital::A

#define BUTTON_SLAPPER          okapi::ControllerDigital::L2

#define BUTTON_HOLD             okapi::ControllerDigital::X
#define BUTTON_COAST            okapi::ControllerDigital::Y
//-----------------------------------------------------------

#endif
