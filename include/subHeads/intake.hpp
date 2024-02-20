#pragma once

#include "pros/motors.hpp"
#include "lemlib/timer.hpp"

class IntakeStateMachine {
    public:
        explicit IntakeStateMachine(std::int8_t port, pros::motor_gearset_e_t gearset);

        enum STATE {
            IDLE,
            INTAKE,
            OUTTAKE,
            E_STOP
        };

        /**
         * @brief Get the current state of the intake
         *
         * @return intake state (as an enum)
         */
        [[nodiscard]] STATE getState() const;

        /**
         * @brief Update the intake state machine
         */
        void update();

        /**
         * @brief Idle the intake
         */
        void idle();

        /**
         * @brief Intake
         */
        void intake();

        /**
         * @brief Outtake
         */
        void outtake();

        /**
         * @brief Emergency stop the intake
         */
        void emergencyStop();

        /**
         * @brief Resume the intake after an emergency stop
         */
        void cancelEmergencyStop();

        /**
         * @brief Detects whether the intake has a ball or not by looking for a spike in voltage draw
         * @note This function can give false positives by hitting a wall or other objects
         *
         * @return Whether the intake has a ball or not
         */
        [[nodiscard]] bool hasBall() const;

        /**
         * @brief Runs the intake
         *
         * @param millis max amount of time the intake will spend running
         *
         * @return Whether the intake has a ball or not
         */
        void grabBall(int millis = INT32_MAX);

    private:
        float wattageThreshold = 4.0;

        pros::Motor* motor;
        STATE state = STATE::IDLE;

        lemlib::Timer timer{0};

        bool isGrabbing = false;
};
