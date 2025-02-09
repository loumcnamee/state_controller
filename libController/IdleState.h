#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "State.h"
//#include "Context.h"

class IdleState : public IState {
public:
    IdleState();
    ~IdleState() = default;
    //CoolingState(const CoolingState &other) = default;
    //CoolingState(CoolingState &&other) = default;
    //CoolingState &operator=(const CoolingState &other) = default;
    //CoolingState &operator=(CoolingState &&other) = default;
    const std::string& name() const;
};

#endif // IDLE_STATE_H

