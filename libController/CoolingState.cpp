#include "CoolingState.h"

CoolingState::CoolingState() : IState{"Cooling"}
{
    setPower(-1.0f);
}

const std::string& CoolingState::name() const {
    return name_;
}



