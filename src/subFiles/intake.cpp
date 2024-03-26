#include "subHeads/intake.hpp"

IntakeStateMachine::IntakeStateMachine(const std::int8_t port, const pros::motor_gearset_e_t gearset) : motor(new pros::Motor(port, gearset)) {
    this->motor->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    this->motor->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    this->motor->tare_position();
}

IntakeStateMachine::STATE IntakeStateMachine::getState() const {
    return this->state;
}

void IntakeStateMachine::update() {
    if (this->isGrabbing) {
        if (this->timer.isDone() || this->hasBall()) {
            this->isGrabbing = false;
            this->idle();
        }
    }

    switch (this->state) {
        case INTAKE: motor->move(127);
            break;
        case OUTTAKE: motor->move(-127);
            break;
        case IDLE: motor->move(0);
            break;
        case E_STOP: motor->move(0);
    }
}

void IntakeStateMachine::idle() {
    if (this->state == STATE::E_STOP) return;
    this->state = STATE::IDLE;
}

void IntakeStateMachine::intake() {
    if (this->state == STATE::E_STOP) return;
    this->state = STATE::INTAKE;
}

void IntakeStateMachine::outtake() {
    if (this->state == STATE::E_STOP) return;
    this->state = STATE::OUTTAKE;
}

void IntakeStateMachine::emergencyStop() {
    this->idle();
    this->state = STATE::E_STOP;
}

void IntakeStateMachine::cancelEmergencyStop() {
    this->state = STATE::IDLE;
}

bool IntakeStateMachine::hasBall() const {
    return (this->motor->get_power()) > (this->wattageThreshold);
}

void IntakeStateMachine::grabBall(int millis) {
    this->isGrabbing = true;
    this->intake();
    this->timer.set(millis);
}