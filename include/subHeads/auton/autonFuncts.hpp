#pragma once
#include "main.h"
#include "subHeads/auton/autonHelpers.hpp"

// Helper movement functions
/**
 * @brief Move the drivetrain with motor powers and time
 * @note Only use for relative motions with low precision
 * @param leftPower The power for the left motor [-127, 127]
 * @param rightPower The power for the right motor [-127, 127]
 * @param time The amount of time to wait
 */
void chassisMovePowers(int leftPower, int rightPower, int time);

void chassisRam(bool forwards = false);

// Auton selector functions
void closeQual_funct();
void closeSafe_funct();
void closeElim_funct();
void farQual_funct();
void farSafe_funct();
void farElim_funct();
void skillsAuton_funct();