#ifndef STATE_H
#define STATE_H

#include <string>



class IState {
protected:
    std::string name_;
    // input power to the system (heater or cooler)
    // + = add heat, - = remove heat
    float power_;

    float setpoint_;
    
public:
    IState(const std::string &name) : name_{name} {}
    virtual ~IState() = default;
    virtual const std::string& name() const = 0;
    void setPower(float pwr) { power_ = pwr; }
    float power() const { return power_; }
    void setSetPoint(float setpoint) { setpoint_ = setpoint; }
    float setPoint() const { return setpoint_; }
};

#endif // STATE_H
