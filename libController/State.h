#ifndef STATE_H
#define STATE_H

#include <string>



class IState {
protected:
    std::string name_;
    
public:
    IState(const std::string &name) : name_{name} {}
    virtual ~IState() = default;
    virtual const std::string& name() const = 0;
};

#endif // STATE_H
