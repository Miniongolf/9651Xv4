#include "subHeads/pneumatics.hpp"

PistonGroup::PistonGroup(const std::vector<pros::ADIDigitalOut>& pistonsVec)
    : pistonsVec(pistonsVec) {}

PistonGroup::PistonGroup(const std::vector<uint8_t>& ports) {
    for (std::uint8_t port : ports) {
        this->pistonsVec.emplace_back(port);
    }
}

PistonGroup::PistonGroup(uint8_t port) {
    this->pistonsVec.emplace_back(port);
}

void PistonGroup::extend() {
    for (pros::ADIDigitalOut piston : this->pistonsVec) {
        piston.set_value(true);
    }
    this->isExtended = true;
}

void PistonGroup::retract() {
    for (pros::ADIDigitalOut piston : this->pistonsVec) {
        piston.set_value(false);
    }
    this->isExtended = false;
}

void PistonGroup::toggle() {
    for (pros::ADIDigitalOut piston : this->pistonsVec) {
        piston.set_value(!this->isExtended);
    }
    this->isExtended = !isExtended;
}

void PistonGroup::set_value(bool extended) {
    for (pros::ADIDigitalOut piston : this->pistonsVec) {
        piston.set_value(extended);
    }
    this->isExtended = extended;
}