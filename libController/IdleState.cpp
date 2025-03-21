#include "IdleState.h"

IdleState::IdleState() : IState{"Idle"}
{
    setPower(0.0f);
}

const std::string& IdleState::name() const {
    return name_;
}