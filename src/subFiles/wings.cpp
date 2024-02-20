#include "subHeads/wings.hpp"

WingsStateMachine::WingsStateMachine(std::uint8_t frontLeftPort, std::uint8_t frontRightPort, std::uint8_t backPort)
    : frontLeft(new pros::ADIDigitalOut(frontLeftPort)), frontRight(new pros::ADIDigitalOut(frontRightPort)), back(new pros::ADIDigitalOut(backPort)) {
    this->frontLeft->set_value(false);
    this->frontRight->set_value(false);
    this->back->set_value(false);
}

WingsStateMachine::STATE WingsStateMachine::getState() const {
    return this->state;
}

void WingsStateMachine::update() {
    switch (this->state) {
        case STATE::RETRACTED:
            this->frontLeft->set_value(false);
            this->frontRight->set_value(false);
            this->back->set_value(false);
            break;
        case STATE::LEFT:
            this->frontLeft->set_value(true);
            this->frontRight->set_value(false);
            this->back->set_value(false);
            break;
        case STATE::RIGHT:
            this->frontLeft->set_value(false);
            this->frontRight->set_value(true);
            this->back->set_value(false);
            break;
        case STATE::FRONT:
            this->frontLeft->set_value(true);
            this->frontRight->set_value(true);
            this->back->set_value(false);
            break;
        case STATE::BACK:
            this->frontLeft->set_value(false);
            this->frontRight->set_value(false);
            this->back->set_value(true);
            break;
    }
}

void WingsStateMachine::retract(WING wing) {
    switch (wing) {
        case LEFT:
            if (this->state == STATE::FRONT) this->state = STATE::RIGHT;
            if (this->state == STATE::LEFT) this->state = STATE::RETRACTED;
            break;
        case RIGHT:
            this->state = (this->state == STATE::LEFT) ? STATE::FRONT : STATE::RIGHT;
            break;
        case FRONT:
            this->state = STATE::FRONT;
            break;
        case BACK:
            this->state = STATE::BACK;
            break;
    }
}

void WingsStateMachine::extend(WING wing) {
    switch (wing) {
        case LEFT:
            this->state = (this->state == STATE::RIGHT) ? STATE::FRONT : STATE::LEFT;
            break;
        case RIGHT:
            this->state = (this->state == STATE::LEFT) ? STATE::FRONT : STATE::RIGHT;
            break;
        case FRONT:
            this->state = STATE::FRONT;
            break;
        case BACK:
            this->state = STATE::BACK;
            break;
    }
}