#ifndef INC_9651XV4_PNEUMATICS_HPP
#define INC_9651XV4_PNEUMATICS_HPP

#include <memory>
#include <vector>

#include "../pros/adi.hpp"

class PistonGroup {
    public:
        /**
         * @brief Piston Group class constructor
         *
         * @param pistonsVec std::vector of pros::ADIDigitalOut objects
         */
        PistonGroup(const std::vector<pros::ADIDigitalOut>& pistonsVec);

        /**
         * @brief Piston Group class constructor
         *
         * @param ports std::vector of ports
         */
        PistonGroup(const std::vector<uint8_t>& ports);

        /**
         * @brief Piston Group class constructor (single piston)
         *
         * @param port port number
         */
        explicit PistonGroup(uint8_t port);

        /**
         * @brief Extends the pistons
         */
        void extend();

        /**
         * @brief Retracts the pistons
         */
        void retract();

        /**
         * @brief Toggles the pistons
         */
        void toggle();

        /**
         * @brief Sets the pistons to the target position
         *
         * @param extended The target position. true for extended, false for retracted.
         */
        void set_value(bool extended);

        bool isExtended = false;

    private:
        std::vector<pros::ADIDigitalOut> pistonsVec;
};

#endif // INC_9651XV4_PNEUMATICS_HPP
