#include "main.h"

#include "okapi/api/odometry/point.hpp"

using namespace okapi;

//---------------------------------Group-definitions---------------------------------------

Motor rightFront(RIGHT_FRONT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightMiddle(RIGHT_MIDDLE, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(RIGHT_BACK, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

Motor leftFront(LEFT_FRONT, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftMiddle(LEFT_MIDDLE, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBack(LEFT_BACK, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive({leftFront, leftMiddle, leftBack}); 
MotorGroup rightDrive({rightFront, rightMiddle, rightBack});

MotorGroup Drive({rightFront, rightMiddle, rightBack, leftFront, leftMiddle, leftBack});

std::shared_ptr<OdomChassisController> drive = ChassisControllerBuilder()
    .withMotors({leftFront, leftMiddle, leftBack}, {rightFront, rightMiddle, rightBack}) 
    .withDimensions(AbstractMotor::gearset::blue, {{WHEEL_SIZE, DRIVE_WIDTH}, okapi::imev5BlueTPR * (GEAR_RATIO)})
    .withOdometry() 
    .buildOdometry();

//-------------------------------------functions------------------------------------------

void print_state(std::string title, const okapi::OdomState& os) {
    printf("%s: %lf, %lf, %lf\n", title.c_str(),
        os.y.convert(okapi::foot), os.x.convert(okapi::foot),
        os.theta.convert(okapi::degree));
}

void print_cur_state() {
    print_state("current state", drive->getState());
}

void updateDrive() {
    pros::lcd::set_text(1, std::to_string(drive->getState().y.convert(okapi::foot))); 
    pros::lcd::set_text(2, std::to_string(drive->getState().x.convert(okapi::foot)));

    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY), 
            controller.getAnalog((ControllerAnalog::rightX)));

    if (controller.getDigital(ControllerDigital::X) == 1){
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold);

    } else if (controller.getDigital(ControllerDigital::Y) == 1){
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
    }
}
