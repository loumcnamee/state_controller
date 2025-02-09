#ifndef HEATING_STATE_H
#define HEATING_STATE_H

#include "State.h"
//#include "Context.h"

class HeatingState : public IState {
public:
    HeatingState();
    ~HeatingState() = default;
    const std::string& name() const;
  
};


#endif // HEATING_STATE_H
