#include "globals.h"
#include "main.h"
#include "pros/abstract_motor.hpp"

const int UNDEF = 50;
//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//drivetrain
pros::MotorGroup leftDrive({-1, -2, -19}, pros::MotorGears::blue);
pros::MotorGroup rightDrive({4, 5, 6}, pros::MotorGears::blue);

//motor ports
pros::Imu inertial(12);

pros::Motor intake(7);
pros::Motor claw(8);
pros::Motor cascade(11);
pros::Rotation verticalEnc(9);
pros::Rotation horizontalEnc(10);
pros::adi::DigitalOut matchload('A');

lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, 8.5);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, 0.5);

//global vars
bool teamRed = true;
int move = 1;

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              12.25, // 12.5 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 3.25" omnis
                              360, // drivetrain rpm is 360 since the gear ratio is 1:0.6
                              2 // horizontal drift is 2 (for now) <--need to be changed
);

lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// odometry settings
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // in ertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                 10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

lemlib::Chassis chassis(drivetrain,
                        lateral_controller, 
                        angular_controller, 
                        sensors
);