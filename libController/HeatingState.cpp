#include "HeatingState.h"

HeatingState::HeatingState() : IState{"Heating"}
{
    
}

const std::string& HeatingState::name() const {
    return name_;
}
