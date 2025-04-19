#include "SetPointState.h"

SetPointState::SetPointState() : IState{"Idle"}
{
    setPower(0.0f);
}

