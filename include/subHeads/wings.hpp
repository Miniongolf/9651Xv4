#pragma once

#include "pros/adi.hpp"

class WingsStateMachine {
    public:
        WingsStateMachine(std::uint8_t frontLeftPort, std::uint8_t frontRightPort, std::uint8_t backPort);

        enum class STATE {
            RETRACTED,
            LEFT,
            RIGHT,
            FRONT,
            BACK
        };

        enum WING {
            LEFT,
            RIGHT,
            FRONT,
            BACK
        };

        /**
         * @brief Get the current state of the wings
         *
         * @return wings state (as an enum)
         */
        [[nodiscard]] STATE getState() const;

        /**
         * @brief Update the wings state machine
         */
        void update();

        /**
         * @brief Retracts selected wing
         */
        void retract(WING wing);

        /**
         * @brief Extends selected wing
         */
        void extend(WING wing);

    private:
        STATE state = STATE::RETRACTED;

        pros::ADIDigitalOut* frontLeft;
        pros::ADIDigitalOut* frontRight;
        pros::ADIDigitalOut* back;
};