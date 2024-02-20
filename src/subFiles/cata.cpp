#include "subHeads/cata.hpp"

CataStateMachine::CataStateMachine(const std::int8_t port, const pros::motor_gearset_e_t gearset) : motor(new pros::Motor(port, gearset)) {
    this->motor->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    this->motor->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    this->motor->tare_position();
}

CataStateMachine::STATE CataStateMachine::getState() const {
    return this->state;
}

void CataStateMachine::update() {
    // Check for matchloading
    if (this->isMatchloading) {
        if (this->timer.isDone() || this->triballsLeft <= 0) {
            this->isMatchloading = false;
            this->triballsLeft = -1;
        } else {
            this->fire();
            if (std::fabs(fmod(this->motor->get_position(), 180)) < 5) {
                this->hasFired = false;
            }
            if (std::fabs(fmod(this->motor->get_position(), 360)) < 5) {
                this->triballsLeft--;
                this->hasFired = true;
            }
        };
    }

    switch (this->state) {
        case FIRING:
            motor->move(127);
            this->isFiring = true;
            break;
        case IDLE:
            motor->move(0);
            this->isFiring = false;
            this->isMatchloading = false;
            break;
        case E_STOP:
            motor->move(0);
            this->isFiring = false;
            this->isMatchloading = false;
    }
}

void CataStateMachine::fire() {
    if (this->state == STATE::E_STOP) return;

    this->state = STATE::FIRING;
}

void CataStateMachine::idle() {
    if (this->state == STATE::E_STOP) return;

    this->state = STATE::IDLE;
}

void CataStateMachine::emergencyStop() {
    this->idle();
    this->state = STATE::E_STOP;
}

void CataStateMachine::cancelEmergencyStop() {
    this->state = STATE::IDLE;
}

void CataStateMachine::matchload(int millis, int triballs) {
    this->timer.set(millis);
    this->timer.resume();
    this->triballsLeft = triballs;

    this->isMatchloading = true;
    this->fire();
}

bool CataStateMachine::getIsFiring() {
    return this->isFiring;
}

bool CataStateMachine::getIsMatchloading() {
    return this->isMatchloading;
}
