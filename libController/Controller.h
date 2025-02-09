#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "State.h"
#include <string>
#include <memory>
#include <variant>
#include <optional>
#include <iostream>
#include "HomeHeatModel.h"
#include "HeatingState.h"
#include "CoolingState.h"
#include "IdleState.h"
#include "Event.h"

using namespace std;
using State = variant<IdleState, HeatingState, CoolingState>;

/* ------------------------------- Transitions ---------------------------------------- */
struct Transitions {
    optional<State> operator()(IdleState &, const EventStop &) {
        cout << "Idle -> Idle" << endl;
        return IdleState{};
    }

    optional<State> operator()(IdleState &, const EventTooHot &) {
        cout << "Idle -> Cooling" << endl;
        return CoolingState{};
    }

    optional<State> operator()(IdleState &, const EventTooCold &) {
        cout << "Idle -> Heating" << endl;
        return HeatingState{};
    }

    optional<State> operator()(HeatingState &s, const EventTooCold &) {
        cout << "Heating -> Heating" << endl;
        return HeatingState{};
    }

    optional<State> operator()(CoolingState &s, const EventTooHot &) {
        cout << "Cooling -> Cooling" << endl;
        return CoolingState{};
    }

    optional<State> operator()(CoolingState &, const EventStop &) {
        cout << "Cooling -> Idle" << endl;
        return IdleState{};
    }

    optional<State> operator()(HeatingState &, const EventStop &) {
        cout << "Heating -> Idle" << endl;
        return IdleState{};
    }
    
    template <typename State_t, typename Event_t>
    optional<State> operator()(State_t &, const Event_t &) const {
        cout << "Unkown" << endl;
        return IdleState{};
    }
};



template <typename StateVariant, typename EventVariant, typename Transitions>
class Controller {
private:
    StateVariant m_curr_state = IdleState{};
    std::unique_ptr<HomeHeatModel> model_;

    void dispatch(const EventVariant &Event);


public:
    Controller();
    template <typename... Events>
    void process(Events... e) { (dispatch(e), ...); }
 

    std::string getStateName() const;

    const float getBuildingTemperature() const { return model_->getBuildingTemperature(); }
    const float getOutsideTemperature() const { return model_->getOutsideTemperature(); }
    const float getInputPower() const { return model_->getInputPower(); }
    const float getFloorArea() const { return model_->getFloorArea(); }
    void setOutsideTemperature(float temp) { model_->setOutisdeTemperature(temp); }
    
    
};

#endif // CONTROLLER_H
