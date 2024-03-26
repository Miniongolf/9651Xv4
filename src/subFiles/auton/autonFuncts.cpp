#include "subHeads/auton/autonFuncts.hpp"
#include "subHeads/opcontrol/opcontrolHelpers.hpp"

// Helper movement functions
void chassisMovePowers(int leftPower, int rightPower, int time, bool wait) {
    chassis.waitUntilDone();
    chassis.tank(leftPower, rightPower);
    pros::delay(time);
    chassis.tank(0, 0);
}

void chassisRam(bool forwards) {
    chassisMovePowers(50, 50, 400);
    chassisMovePowers(-127, -127, 400, false);
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

void skillsAuton_funct(bool isDriver) {
    std::cout << "Auton skills\n";

    chassis.setPose(-45, -57, 135);

    // Score preloads
    chassis.moveToPose(-60, -28, 180, 1000, {.forwards = false, .minSpeed = 100});
    chassisRam();
    chassis.setPose(-60, -32, 180); // odom reset on net

    // Move to shooting position
    chassis.moveToPose(-56, -47, -115, 2000, {.maxSpeed = 70}); // Move to matchload bar
    wings.extend(WingsStateMachine::FRONT); // Extend front wings

    // Matchload 50 triballs (max 30 seconds)
    cata.matchload(50, 1'800'000);

    while (cata.getIsMatchloading()) {
        if (isDriver) {
            gamepad1.update();
            drive(gamepad1);
            if (gamepad1.x.pressed) break;
        }
        pros::delay(20);
    }

    cata.idle();
    wings.retract(WingsStateMachine::FRONT);

    if (isDriver) return; // Exit early if driver control

    // Cross to other side
    chassis.moveToPoint(-29, -58, 2000, {.forwards = false}); // Interpolate to bowling position
    chassis.moveToPose(-32, -58, -90, 2000, {.forwards = false}); // Move to bowling position
    debug::printPose();
    chassis.moveToPose(45, -58, -90, 2000, {.forwards = false, .minSpeed = 70, .earlyExitRange = 24});

    // Right push
    chassis.moveToPose(48, -48, -135, 1000, {.forwards = false, .minSpeed = 70, .earlyExitRange = 10});
    chassis.moveToPose(60, -20, 180, 2000, {.forwards = false, .minSpeed = 127});
    chassisRam();

    // Middle push 1
    chassisMovePowers(50, 50, 750);
    chassis.turnToHeading(-45, 1000);
    chassis.moveToPoint(29, -33, 2000);
    chassis.moveToPose(18, -10, 0, 2000);
    chassis.waitUntilDone();
    wings.extend(WingsStateMachine::FRONT);
    chassis.moveToPose(38, -7, 90, 2000);
    chassisMovePowers(50, 50, 400);
    chassis.arcade(0, 0);

    while (true) pros::delay(50);
}