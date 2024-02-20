#include "main.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

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
    while (true) {
        // Cata
        if (gamepad1.x.pressed) { (cata.getIsFiring()) ? cata.idle() : cata.fire(); }

        // Wings
        (gamepad1.dpadDown.pressed || gamepad1.lt.pressed) ? wings.extend(WingsStateMachine::LEFT) : wings.retract(WingsStateMachine::LEFT);
        (gamepad1.b.pressed || gamepad1.lt.pressed) ? wings.extend(WingsStateMachine::RIGHT) : wings.retract(WingsStateMachine::RIGHT);
        (gamepad1.lb.pressed) ? wings.extend(WingsStateMachine::BACK) : wings.retract(WingsStateMachine::BACK);

        // Hang
        if (gamepad1.dpadRight.pressed) hang.raise();
        else if (gamepad1.y.pressed) hang.lower();
        else if ((int)gamepad1.a > 250) hang.hang();
        else hang.idle();

        // Intake
        if (gamepad1.rt) intake.intake();
        else if (gamepad1.rb) intake.outtake();
        else intake.idle();



        pros::delay(10); // DO NOT DELETE
    }
}
#pragma clang diagnostic pop