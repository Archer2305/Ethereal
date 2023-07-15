#include "main.h"
#include "drive.hpp"  

#include "okapi/api/odometry/point.hpp"

#define WHEEL_SIZE      4.125_in
#define DRIVE_WIDTH     0_in
#define GEAR_RATIO      ((double)1 / 1)

using namespace okapi;

//---------------------------------Group-definitions---------------------------------------

Motor rightFront(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightTop(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBottom(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

Motor leftFront(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftTop(1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBottom(1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive ({leftFront, leftTop, leftBottom}); 
MotorGroup rightDrive({rightFront, rightTop, rightBottom});

MotorGroup Drive({rightFront, rightTop, rightBottom, leftFront, leftTop, leftBottom});

std::shared_ptr<OdomChassisController> drive = ChassisControllerBuilder()
    .withMotors({leftFront, leftTop, leftBottom}, {rightFront, rightTop, rightBottom}) 
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
    pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot))); 
    pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot)));

    if (controller.getAnalog(ControllerAnalog::leftX) == 0){
        drive->getModel()->arcade(0.5 * controller.getAnalog(ControllerAnalog::rightY), 
                0.5 * controller.getAnalog((ControllerAnalog::rightX)));
    }

    if (controller.getAnalog(ControllerAnalog::rightX) == 0){
        drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY), 
                controller.getAnalog((ControllerAnalog::leftX)));
    }

    if (controller.getDigital(ControllerDigital::X) == 1){
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold);

    } else if (controller.getDigital(ControllerDigital::Y) == 1){
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
    }
}
