#include "main.h"
#include "subHeads/auton/autonFuncts.hpp"

// Auton selection enum
/*
skills = 0,
closeQual = 1,
closeSafe = 2,
closeElim = 3,
farQual = -1,
farSafe = -2,
farElim = -3
*/

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
void autonomous() {
    auto autonMode = static_cast<AutoSelect>(selector::auton);

    switch (autonMode) {
        case AutoSelect::skills:
            if (isCompMatch) {
                cata.matchload(10);
//                skillsAuton_funct();
            } else {
                chassis.setPose(0, 0, 0);
                chassis.turnToHeading(90, 2000);
                debug::printPose();
                chassis.moveToPose(48, 0, 90, 2000);
                debug::printPose();
            }
            break;
        case AutoSelect::closeQual: closeQual_funct(); break;
        case AutoSelect::closeSafe: closeSafe_funct(); break;
        case AutoSelect::closeElim: closeElim_funct(); break;
        case AutoSelect::farQual: farQual_funct(); break;
        case AutoSelect::farSafe: farSafe_funct(); break;
        case AutoSelect::farElim: farElim_funct(); break;

    }
}