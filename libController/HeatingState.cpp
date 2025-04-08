#include "HeatingState.h"

HeatingState::HeatingState() : IState{"Heating"}
{
    setPower(1.0f);
    int x;
}

const std::string& HeatingState::name() const {
    return name_;
}
