#include "IdleState.h"
#include "constants.h"

IdleState::IdleState() : IState{"Idle"}
{
    setPower(model_defaults::initialInputPower);
}

