#include "main.h"
#include "lemlib/api.hpp"



double track_width = 12.0; //placehold
float wheel_diameter = lemlib::Omniwheel::NEW_325; //placehold :sob:
int drive_rpm = 450;
int horizontal_drift = 2;



pros::Controller master(pros::E_CONTROLLER_MASTER);

//motor ports
pros::MotorGroup left_mg({-1, -2, 3}, pros::MotorGearset::blue);
pros::MotorGroup right_mg({4, 5, -6}, pros::MotorGearset::blue);

lemlib::Drivetrain drivetrain(&left_mg,&right_mg,
								track_width, //track width
								wheel_diameter, //wheel type
								drive_rpm,
								horizontal_drift);

//PLACEHOLDER FOR AUTON LATER
//odometry and tracking 
/* PLACEHOLDER
pros::Imu imu(10);//odometry imu port; 
pros::Rotation rotation_sensor(1); // rotation sensor port
*/
//sensors
lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, nullptr);

//PID values
lemlib::ControllerSettings lateral(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angular(2, 0, 10, 3, 1, 100, 3, 500, 0);

//------
lemlib::Chassis chassis(drivetrain, lateral, angular, sensors);


// -CUSTOM FUNCTIONS--
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Center Button Pressed");
	} else {
		pros::lcd::clear_line(2);
	}
}

// --DEFAULT FUNCTIONS--

/**
 * runs immediately as program starts - keep short
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "sending you home");
	//chassis.calibrate();
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE); //resist movement when no joystick
	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		//control
		int throttle = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		chassis.arcade(throttle, turn);
		pros::delay(10); //Run for 10 ms then update
	}
}