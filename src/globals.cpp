#include "globals.hpp"

#define UNUSED_PORT 0

// GAMEPADS
nicklib::Gamepad gamepad1(pros::E_CONTROLLER_MASTER);
nicklib::Gamepad gamepad2(pros::E_CONTROLLER_PARTNER);

// SENSORS
pros::IMU imu(18);
// pros::Distance cataDistance(UNUSED_PORT);
// pros::Distance leftDistance(UNUSED_PORT);
// pros::Distance rightDistance(UNUSED_PORT);

// DRIVE MOTOR GROUPS
pros::MotorGroup leftMotors({
    pros::Motor(-20, pros::E_MOTOR_GEAR_BLUE), // m1
    pros::Motor(-16, pros::E_MOTOR_GEAR_BLUE), // m2
    pros::Motor(-11, pros::E_MOTOR_GEAR_BLUE), // m3
    pros::Motor(-15, pros::E_MOTOR_GEAR_GREEN) // 5.5 watt motor
});

pros::MotorGroup rightMotors({
    pros::Motor(10, pros::E_MOTOR_GEAR_BLUE), // m1
    pros::Motor(3, pros::E_MOTOR_GEAR_BLUE), // m2
    pros::Motor(1, pros::E_MOTOR_GEAR_BLUE), // m3
    pros::Motor(4, pros::E_MOTOR_GEAR_GREEN) // 5.5 watt motor
});

// SUBSYS STATE MACHINE
CataStateMachine cata(5, pros::E_MOTOR_GEAR_GREEN);
IntakeStateMachine intake(-12, pros::E_MOTOR_GEAR_GREEN);
WingsStateMachine wings('G', 'H', 'F');
HangStateMachine hang(0, pros::E_MOTOR_GEAR_GREEN, 'A');

// CHASSIS PID
lemlib::ControllerSettings lateralController(20, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             30, // derivative gain (kD)
                                             3, // anti-windup
                                             1, // small error range, in inches
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in inches
                                             500, // large error range timeout, in milliseconds
                                             20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularController(7, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             50, // derivative gain (kD)
                                             3, // anti-windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// LEMLIB CHASSIS
lemlib::Drivetrain drivetrain(&leftMotors, // left drivetrain motors
                              &rightMotors, // right drivetrain motors
                              12.5, // track width
                              lemlib::Omniwheel::NEW_325, // wheel diameter
                              450, // wheel rpm
                              8 // chase power
);

lemlib::OdomSensors odomSensors(nullptr,
                                nullptr,
                                nullptr,
                                nullptr,
                                nullptr // inertial sensor
);

lemlib::Chassis chassis(drivetrain, lateralController, angularController, odomSensors);

// MISC
bool isCompMatch = false;