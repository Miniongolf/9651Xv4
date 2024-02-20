#include "subHeads/auton/autonHelpers.hpp"

// CLOSE POSITIONS
lemlib::Pose closeMatchLoadPose(-51, -49, -45);
lemlib::Pose closeTouchBarPose(-15.5, -56, 90);

lemlib::Pose closeLeftBall(3.4, 0); // Barrier ball
lemlib::Pose closeRightBall(24, 0); // Middle ball

// FAR POSITIONS
lemlib::Pose farTouchBarPose(5, -60, -90);
lemlib::Pose farMatchLoadPose(0, 0, 0);

lemlib::Pose farLeftBall(3.4, 0); // Far long barrier ball
lemlib::Pose farRightBall(24, 0); // Far middle ball
lemlib::Pose farCloseBall(3.4, -24); // Close long barrier ball
lemlib::Pose farBarBall(0, -60); // Elevation bar ball

void debug::printPose(bool wait) {
    if (wait) chassis.waitUntilDone();
    std::printf("x: %f | y: %f | θ: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
}

/**
 * @brief Detects a collision by looking for a spike in power draw
 *
 * @return true if a collision is detected
 */
 bool detectCollision() {
     return (leftMotors.get_current_draws()[0] > 1500 && rightMotors.get_current_draws()[0] > 1500);
 }

/**
 * @brief Calculate the target position to move to based on the ball position, intake offset, and the target angle
 *
 * @param ballPoint The position of the ball as a lemlib::Pose
 * @param targetAngle The angle to end at (in degrees)
 */
lemlib::Pose calcTargetPose(lemlib::Pose ballPoint, float targetAngle) {
    float x = ballPoint.x + intakeOffset * cos(targetAngle+90);
    float y = ballPoint.y + intakeOffset * sin(targetAngle+90);
    return {x, y, targetAngle};
}

/**
 * @brief Move to the ball at the given position and angle
 *
 * @param ballPoint position of the ball as a lemlib::Pose
 * @param targetAngle target heading in degrees
 * @param timeout longest time the robot can spend moving
 * @param grabDistance movement distance to wait before grabbing. -1 by default, meaning no grab.
 * @param params struct to simulate named parameters
 */
void moveToBall(lemlib::Pose ballPoint, float targetAngle, int timeout, float grabDistance,
                lemlib::MoveToPoseParams params) {
    lemlib::Pose targetPose = calcTargetPose(ballPoint, targetAngle);
    chassis.moveToPose(targetPose.x, targetPose.y, targetPose.theta, timeout, params);

    // Grab ball if grabDistance is set
    if (grabDistance != -1) {
        chassis.waitUntil(grabDistance);
        intake.intake();
        while (!intake.hasBall() && chassis.isInMotion()) pros::delay(50);
        intake.idle();
    } else {
        chassis.waitUntilDone();
    }
}