#pragma once

#include <cmath>

#include "pros/motors.hpp"
#include "lemlib/timer.hpp"

class CataStateMachine {
    public:
        explicit CataStateMachine(std::int8_t port, pros::motor_gearset_e_t gearset);

        enum STATE {
            FIRING,
            IDLE,
            E_STOP
        };

        /**
         * @brief Get the current state of the catapult
         *
         * @return catapult state (as an enum)
         */
        [[nodiscard]] STATE getState() const;

        /**
         * @brief Update the catapult state machine
         */
        void update();

        /**
         * @brief Fire the catapult
         */
        void fire();

        /**
         * @brief Idle the catapult
         */
        void idle();

        /**
         * @brief Emergency stop the catapult
         */
        void emergencyStop();

        /**
         * @brief Resume the catapult after an emergency stop
         */
        void cancelEmergencyStop();

        /**
         * @brief Matchload the catapult
         *
         * @param millis max amount of time the catapult will spend matchloading
         * @param triballs how many triballs to fire
         */
        void matchload(int millis = INT32_MAX, int triballs = -1);

        bool getIsFiring();
        bool getIsMatchloading();

    private:
        pros::Motor* motor;
        lemlib::Timer timer{0};

        STATE state = STATE::IDLE;

        bool hasFired = false, isFiring = false, isMatchloading = false;
        int triballsLeft = 0;
};