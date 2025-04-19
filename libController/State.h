#ifndef STATE_H
#define STATE_H

#include <string>



class IState {
private:
    std::string name_;
    // input power to the system (heater or cooler)
    // + = add heat, - = remove heat
    float power_;

    float setpoint_;
    
public:
    IState(const std::string &name, const float power, const float setpoint_) : name_{name},  power_{power}, setpoint_{setpoint_} {}
    explicit IState(const std::string &name) : name_{name}, power_{0.0F}, setpoint_{0.0F} {}    
    const std::string& name() const;
    void setPower(float pwr) { power_ = pwr; }
    float power() const { return power_; }
    void setSetPoint(float setpoint) { setpoint_ = setpoint; }
    float setPoint() const { return setpoint_; }
};

#endif // STATE_H
