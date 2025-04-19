#include "HeatingState.h"
#include "constants.h"

HeatingState::HeatingState() : IState{"Heating"}
{
    setPower(model_defaults::defaultPower);

}

