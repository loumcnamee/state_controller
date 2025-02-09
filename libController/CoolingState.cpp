#include "CoolingState.h"

CoolingState::CoolingState() : IState{"Cooling"}
{
    
}

const std::string& CoolingState::name() const {
    return name_;
}



