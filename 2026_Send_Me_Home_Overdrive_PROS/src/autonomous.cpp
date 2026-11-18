#include "autonomous.h"
#include "globals.h"
#include "main.h"
#include "pros/llemu.hpp"

auto &outbput = std::cout;

void Autonomous::constantlyPrintPose() {
    while (true) {
        pros::lcd::print(0, "x: %f", chassis.getPose().x);
        pros::lcd::print(1, "Y: %f", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
        pros::delay(50);
    }
}

void Autonomous::init() {
    // inertial.reset(true);
    // inertial.tare();
    // while (inertial.is_calibrating()) {
    //     pros::delay(10);
    //     pros::lcd::print(0, "calibrating");
    // }
    // chassis.calibrate();
    // chassis.setPose({0,0,0});
    // // optical.set_led_pwm(100); <--optical sensor (will be put in later)
    // pros::Task printPoseTask(Autonomous::constantlyPrintPose);  //multithreading: constantly print position, seperate from main code.*/

    chassis.calibrate();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
} 

void Autonomous::IntakeMech() {
    intake.move_voltage(12000);
    conveyer.move_voltage(-12000);
}

void Autonomous::outtaketomid() {
    intake.move_voltage(12000);
    conveyer.move_voltage(12000);
    //outtake.move_voltage(-12000);
}



void Autonomous::tuneAngularPID() {
    chassis.setPose({0,0,0});
    chassis.turnToHeading(90, 2000, {}, false); // 90도에서만 이상하게 돌고 또 360에서는 왜 정상으로 뜸????
    pros::delay(1000);
    chassis.turnToHeading(180,2000,{},false);
    pros::delay(1000);
    chassis.turnToHeading(270, 2000,{},false);
    pros::delay(1000);
    chassis.turnToHeading(360,2000,{},false);
}

void Autonomous::tuneLateralPID() {
    chassis.setPose({0,0,0});
    chassis.moveToPoint(0,30, 20000, {}, false);
    chassis.moveToPoint(0, 0, 20000, {.forwards = false}, false);
}

void Autonomous::RedDriveMech() {

    move(-1);
    pros::delay(50);
    stop();

    move(1);
    pros::delay(500);

    move(-1);
    pros::delay(350);

    move(1);
    pros::delay(500);

    move(-1);
    pros::delay(350);

    stop();
    




    // leftDrive.move_voltage(-60000);
    // rightDrive.move_voltage(-50000);
    // pros::delay(200);
    // leftDrive.move_voltage(0);
    // rightDrive.move_voltage(0);
    // pros::delay(200);
    // leftDrive.move_voltage(60000);
    // rightDrive.move_voltage(50000);
    // pros::delay(300);
    // leftDrive.move_voltage(0);
    // rightDrive.move_voltage(0);
    // pros::delay(200);
    // leftDrive.move_voltage(-60000);
    // rightDrive.move_voltage(-50000);
    // pros::delay(300);
    // leftDrive.move_voltage(0);
    // rightDrive.move_voltage(0);
    // pros::delay(200);
    // leftDrive.move_voltage(60000);
    // rightDrive.move_voltage(50000);
    // pros::delay(300);
    // leftDrive.move_voltage(0);
    // rightDrive.move_voltage(0);
    // pros::delay(200);

    // leftDrive.move_voltage(-60000);
    // rightDrive.move_voltage(-50000);
    // pros::delay(300);

}

void Autonomous::move(int multiplier) {
    leftDrive.move_voltage(multiplier*60000);
    rightDrive.move_voltage(multiplier*50000);
}

void Autonomous::stop() {
    move(0);
    pros::delay(50);
}

void Autonomous::BlueDriveMech() {
    RedDriveMech();
    // leftDrive.move_voltage(-6000);
    // rightDrive.move_voltage(-6000);
    // pros::delay(1000);
    // leftDrive.move_voltage(6000);
    // rightDrive.move_voltage(6000);
    // pros::delay(1100);
    // leftDrive.move_voltage(-600);
    // rightDrive.move_voltage(-600);
    // pros::delay(1100);
    // leftDrive.move_voltage(0);
    // rightDrive.move_voltage(0);
}   