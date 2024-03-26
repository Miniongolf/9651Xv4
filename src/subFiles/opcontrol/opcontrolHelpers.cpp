#include "subHeads/opcontrol/opcontrolHelpers.hpp"

void updateAllSystems() {
    // Gamepads
    gamepad1.update();
    gamepad2.update();

    // Cata
    cata.update();

    // Wings
    wings.update();

    // Hang
    hang.update();

    // Intake
    intake.update();
}

std::array<float, 2> processSticks(nicklib::Gamepad& gamepad) {
    float forwardsVel = gamepad.leftY, turnVel = gamepad.rightX;

    forwardsVel = nicklib::deadzone(forwardsVel, STICK_DEADZONE);
    turnVel = nicklib::deadzone(turnVel, STICK_DEADZONE);

    forwardsVel = nicklib::curveInput(forwardsVel, STICK_CURVE_GAIN);
    turnVel = nicklib::curveInput(turnVel, STICK_CURVE_GAIN);

    float leftVel = forwardsVel + turnVel, rightVel = forwardsVel - turnVel;

    return {forwardsVel, turnVel * TURN_MULTIPLIER};
}

void drive(nicklib::Gamepad& gamepad) {
    float forwardsVel = gamepad.leftY, turnVel = gamepad.rightX;

    forwardsVel = nicklib::deadzone(forwardsVel, STICK_DEADZONE);
    turnVel = nicklib::deadzone(turnVel, STICK_DEADZONE);

    forwardsVel = nicklib::curveInput(forwardsVel, STICK_CURVE_GAIN);
    turnVel = nicklib::curveInput(turnVel, STICK_CURVE_GAIN);

    float leftVel = forwardsVel + turnVel, rightVel = forwardsVel - turnVel;

    // Correct for motors out of power range while preserving angular velocity
    if (leftVel > 1) {
        leftVel = 1;
        rightVel = 1 - 2*turnVel;
    } else if (leftVel < -1) {
        leftVel = -1;
        rightVel = -1 - 2*turnVel;
    } else if (rightVel > 1) {
        leftVel = 1 + 2*turnVel;
        rightVel = 1;
    } else if (rightVel < -1) {
        leftVel = -1 + 2*turnVel;
        rightVel = -1;
    }

    chassis.tank(leftVel*127, rightVel*127);
}