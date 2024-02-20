#include "subHeads/auton/autonFuncts.hpp"

// Helper movement functions
void chassisMovePowers(int leftPower, int rightPower, int time) {
    chassis.waitUntilDone();
    chassis.tank(leftPower, rightPower);
    pros::delay(time);
    chassis.tank(0, 0);
}

void chassisRam(bool ) {
    chassisMovePowers(40, 40, 750);
    chassisMovePowers(-70, -70, 500);
}

// Auton selector functions
void closeQual_funct() {
    std::cout << "Close qual auto \n";

}

void closeSafe_funct() {
    std::cout << "Close safe auto \n";

}

void closeElim_funct() { std::cout << "Close elim auto \n"; }

void farQual_funct() {
    std::cout << "Far 3-ball \n";
    chassis.setPose(24, -58, -90); // Set start pose
    moveToBall(farBarBall, -90, 2000, 0); // Grab elevation bar ball
    chassis.moveToPose(50, -60, 90, 2000, {.forwards = false}); // Interpolation to matchload zone
    chassis.moveToPose(farMatchLoadPose.x, farMatchLoadPose.y, farMatchLoadPose.theta, 2000,
                       {.lead = 0.6}); // Interpolation to matchload
}

void farSafe_funct() {
    std::cout << "Far safe \n";
    chassis.setPose(0, 0, 0);
    chassisMovePowers(-127, -127, 750);
    chassisRam();
    chassisMovePowers(70, 70, 500);

    pros::delay(500);
    chassis.turnToHeading(45, 1000);
}

void farElim_funct() {
    std::cout << "Far 6-ball rush \n";
    chassis.setPose(50, -58, -45); // Set start pose
    chassis.moveToPose(24, -18, -15, 2000,
                       {.lead = 0.6, .minSpeed = 100, .earlyExitRange = 5}); // Interpolation to 1st triball
    moveToBall(farRightBall, -50, 2000, 48, {.lead = 0.5}); // Grab 1st triball

    chassis.turnToHeading(90, 1000); // Turn to face net
    chassis.waitUntilDone();
    wings.extend(WingsStateMachine::FRONT);

    // chassis.waitUntilDone();
    // frontWings.extend(); // Extend wings to hit 2nd triball
    // chassis.moveToPose(46, -6, 90, 2000, {.lead=0.6, .minSpeed=127, .earlyExitRange=2}); // Score both
    // chassis.waitUntilDone();
    // frontWings.retract(); // Retract wings
    // chassis.moveToPoint(34.27, -15.49, 1000, false); // Back away from net
    // chassis.moveToPoint(12, -21, 2000, {}); // Grab 3rd triball
    // chassis.moveToPose(48, -13, 90, 2000, {.minSpeed=127, .earlyExitRange=2}); // Score 3rd triball
    // chassis.moveToPoint(37, -42, 1000); // Move away from the net backwards
    // chassis.moveToPose(6, -58, -90, 2000, {.lead=0.6, .earlyExitRange=2}); // Grab 4th triball
    // chassis.moveToPose(61, -49, 45, 2000, {.lead=0.6});

    // chassis.setPose(46, -9, 44);
}

void skillsAuton_funct() {
    std::cout << "Auton skills\n";
}