#include "IdleState.h"

IdleState::IdleState() : IState{"Idle"}
{
    
}

const std::string& IdleState::name() const {
    return name_;
}