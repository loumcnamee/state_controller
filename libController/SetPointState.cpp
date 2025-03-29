#include "SetPointState.h"

SetPointState::SetPointState() : IState{"Idle"}
{
    setPower(0.0f);
}

const std::string& SetPointState::name() const {
    return name_;
}