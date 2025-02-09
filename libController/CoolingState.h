#ifndef COOLING_STATE_H
#define COOLING_STATE_H

#include "State.h"
//#include "Context.h"

class CoolingState : public IState {

    public:
        CoolingState();
        ~CoolingState() = default;
        //CoolingState(const CoolingState &other) = default;
        //CoolingState(CoolingState &&other) = default;
        //CoolingState &operator=(const CoolingState &other) = default;
        //CoolingState &operator=(CoolingState &&other) = default;
        const std::string& name() const;
    
};


#endif // COOLING_STATE_H
