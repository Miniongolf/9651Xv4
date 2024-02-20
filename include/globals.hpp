#pragma once

#include "pros/distance.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"

#include "lemlib/api.hpp"

#include "nicklib/gamepad.hpp"

#include "subHeads/pneumatics.hpp"
#include "subHeads/cata.hpp"
#include "subHeads/intake.hpp"
#include "subHeads/hang.hpp"
#include "subHeads/wings.hpp"

// GAMEPADS
extern nicklib::Gamepad gamepad1;
extern nicklib::Gamepad gamepad2;

// SENSORS
extern pros::IMU imu; // Inertial Measurement Unit
// extern pros::Distance cataDistance; // Catapult distance sensor
// extern pros::Distance leftDistance; // Left distance sensor
// extern pros::Distance rightDistance; // Right distance sensor

// DRIVE MOTOR GROUPS
extern pros::MotorGroup leftMotors; // Left side drivetrain motor group (normal)
extern pros::MotorGroup rightMotors; // Right side drivetrain motor group (normal)

// SUBSYS STATE MACHINES
extern IntakeStateMachine intake; // Intake state machine
extern CataStateMachine cata; // Catapult state machine
extern WingsStateMachine wings; // Wings state machine
extern HangStateMachine hang; // Hang state machine

// CHASSIS PID
extern lemlib::ControllerSettings lateralController; // LemLib Lateral PID
extern lemlib::ControllerSettings angularController; // LemLib Turning PID

// LEMLIB CHASSIS
extern lemlib::Drivetrain drivetrain; // LemLib Drivetrain
extern lemlib::OdomSensors odomSensors; // LemLib Odometry sensors
extern lemlib::Chassis chassis; // LemLib Chassis

// MISC
extern bool isCompMatch;