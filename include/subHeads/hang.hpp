#pragma once

#include "pros/motors.hpp"
#include "pros/adi.hpp"

class HangStateMachine {
    public:
        explicit HangStateMachine(std::int8_t motorPort, pros::motor_gearset_e_t gearset, std::int8_t ratchetPort);

        enum STATE {
            IDLE,
            RAISING,
            LOWERING,
            HANGING
        };

        /**
         * @brief Get the current state of the hang
         *
         * @return hang state (as an enum)
         */
        [[nodiscard]] STATE getState() const;

        /**
         * @brief Update the hang state machine
         */
        void update();

        /**
         * @brief Idle the hang
         */
        void idle();

        /**
         * @brief Raise the hang arm
         */
        void raise();

        /**
         * @brief Lower the hang arm
         */
        void lower();

        /**
         * @brief Hang the robot
         */
        void hang();
    private:
        STATE state = IDLE;

        pros::Motor* motor;
        pros::ADIDigitalOut* ratchetPiston;
};