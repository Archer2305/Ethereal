#include "main.h"
// #include "drive.hpp"  
#include "okapi/api/odometry/point.hpp"
using namespace okapi;

Motor rightFront(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);// motor for the front(drive)
Motor rightTop(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);// the right motor on he top, back (drive)
Motor rightBottom(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);// right motor on the bottom,back (drive)

Motor leftFront(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);//motor for the front (drive)
Motor leftTop(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);//the right motor on he top, back (drive)
Motor leftBottom(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);// left motor on the bottom,back (drive)

MotorGroup leftDrive ({leftFront,leftTop,leftBottom}); //define the left side of the drive as a motor group to allow cleaner code
MotorGroup rightDrive({rightFront,rightTop,rightBottom});//define the left side of the drive as a motor group to allow cleaner code
MotorGroup Drive({rightFront,rightTop,rightBottom,leftFront,leftTop,leftBottom});
//motor groups apply the method to each motor but with one line of code 

  std::shared_ptr<OdomChassisController> drive =ChassisControllerBuilder()
    .withMotors({leftFront, leftTop, leftBottom}, {rightFront, rightTop, rightBottom}) //defines the left and right side of the drive
    .withDimensions(  AbstractMotor::gearset::blue, {{4.125_in, 99999999999999_in}, okapi::imev5BlueTPR*  79999999999./39999999999.})
    .withOdometry() //specifies the tracking wheels dimentions
    .buildOdometry();
    //this creates a drive as an object with PID and the default odometry functions, most of the default odom functions suck tho so we make our own in odom files


  void updateDrive(){
    //the following line is reversed to match the cartesian plane ( math plane) 
    //drive->getState().x.convert(okapi::foot) is odometry 
    //1 tile is 2 feet btw
      pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot))); //displays the Y coordinate on the LCD of the screen per tick
      pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot))); //displays the X coordinate on the LCD of the screen per tick

    // drive -> getModel() -> tank(-translate1.power, -translate1.power); 
    if(controller.getAnalog(ControllerAnalog::leftX)==0){
     drive -> getModel() -> arcade(0.5*controller.getAnalog(ControllerAnalog::rightY), 0.5 * controller.getAnalog((ControllerAnalog::rightX)));
    }
    
    if(controller.getAnalog(ControllerAnalog::rightX)==0){
    drive -> getModel() -> arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog((ControllerAnalog::leftX)));
    }
    if (controller.getDigital(ControllerDigital::X) == 1){
      leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold); //his makes this motors hold its current position to the best of its ability, 
      rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold);//if its pushed with x units of force it will put -x units of force

    }
    else if (controller.getDigital(ControllerDigital::Y) == 1){
      leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast); //this is similar to a gas car and will roll or, "coast"
      rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
      
    }
 
  }
