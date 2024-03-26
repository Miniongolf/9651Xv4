#pragma once

#include "main.h"

constexpr float STICK_CURVE_GAIN = 2;
constexpr float STICK_DEADZONE = 0.1;
constexpr float TURN_MULTIPLIER = 0.7;

enum class DriveModes {
    NORMAL,
    TAKEOVER
};

void updateAllSystems();

std::array<float, 2> processSticks(nicklib::Gamepad& gamepad);

void drive(nicklib::Gamepad& gamepad);