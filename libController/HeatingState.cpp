#include "HeatingState.h"

HeatingState::HeatingState() : IState{"Heating"}
{
    setPower(1.0f);

}

const std::string& HeatingState::name() const {
    return name_;
}
