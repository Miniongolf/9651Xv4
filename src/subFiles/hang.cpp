#include "subHeads/hang.hpp"

HangStateMachine::HangStateMachine(std::int8_t motorPort, pros::motor_gearset_e_t gearset, std::int8_t ratchetPort)
    : motor(new pros::Motor(motorPort, gearset)), ratchetPiston(new pros::ADIDigitalOut(ratchetPort)) {
    this->motor->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    this->ratchetPiston->set_value(false);
}

HangStateMachine::STATE HangStateMachine::getState() const {
    return this->state;
}

void HangStateMachine::update() {
    switch (this->state) {
        case IDLE:
            this->motor->move(0);
            break;
        case RAISING:
            this->motor->move(127);
            break;
        case LOWERING:
            this->motor->move(-127);
            break;
        case HANGING:
            this->motor->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            this->motor->move(0);
            pros::delay(100);
            this->ratchetPiston->set_value(true);
            break;
    }
}

void HangStateMachine::idle() {
    if (this->state == HANGING) return;
    this->state = IDLE;
}

void HangStateMachine::raise() {
    if (this->state == HANGING) return;
    this->state = RAISING;
}

void HangStateMachine::lower() {
    if (this->state == HANGING) return;
    this->state = LOWERING;
}

void HangStateMachine::hang() {
    this->state = HANGING;
}