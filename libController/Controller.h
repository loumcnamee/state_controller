#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "State.h"
#include <string>
#include <memory>
#include <variant>
#include <optional>
#include <iostream>
#include <algorithm>
#include "HomeHeatModel.h"
#include "HeatingState.h"
#include "CoolingState.h"
#include "IdleState.h"
#include "Event.h"
#include "DiurnalSurfaceModel.h"
#include "constants.h"
//using std::variant;
// using std::optional;
//using std::cout;
//using std::endl;
// using std::move;
// using std::string;



//template <typename StateVariant, typename EventVariant, typename Transitions>
struct timeOfDay {
    float hours;  // 0-24 hours
    
    explicit timeOfDay(float hour) : hours(std::clamp(hour, 0.0F, physical_constants::hoursPerDay)) {}
    explicit operator float() const { return hours; }
};

using State = std::variant<IdleState, HeatingState, CoolingState>;

/* ------------------------------- Transitions ---------------------------------------- */
struct Transitions {
    std::optional<State> operator()(IdleState & state, const EventStop & event) {
        std::cout << "Idle -> Idle" << std::endl;
        return IdleState{};
    }

    std::optional<State> operator()(IdleState & state, const EventTooHot &event) {
        std::cout << "Idle -> Cooling" << std::endl;
        return CoolingState{};
    }

    std::optional<State> operator()(IdleState & state, const EventTooCold &event) {
        std::cout << "Idle -> Heating" << std::endl;
        return HeatingState{};
    }

    std::optional<State> operator()(HeatingState &state, const EventTooCold &event) {
        std::cout << "Heating -> Heating" << std::endl;
        return HeatingState{};
    }

    std::optional<State> operator()(CoolingState &state, const EventTooHot &event) {
        std::cout << "Cooling -> Cooling" << std::endl;
        return CoolingState{};
    }

    std::optional<State> operator()(CoolingState &state, const EventStop &event) {
        std::cout << "Cooling -> Idle" << std::endl;
        return IdleState{};
    }

    std::optional<State> operator()(HeatingState & state, const EventStop & event) {
        std::cout << "Heating -> Idle" << std::endl;
        return IdleState{};
    }
    
    template <typename State_t, typename Event_t>
    std::optional<State> operator()(State_t & state, const Event_t & event) const {
        std::cout << "Unkown" << std::endl;
        return IdleState{};
    }
};



template <typename StateVariant, typename EventVariant, typename Transitions>
class Controller {
private:
    StateVariant m_curr_state = IdleState{};
    std::unique_ptr<HomeHeatModel> model_;
    std::unique_ptr<DiurnalSurfaceTemperatureModel> surfaceTempModel_;

    void dispatch(const EventVariant &Event);


public:
    Controller();
    template <typename... Events>
    void process(Events... event) { (dispatch(event), ...); }
 

    std::string getStateName() const;

    float getBuildingTemperature() const { return model_->getBuildingTemperature(); }
    float getOutsideTemperature() const { return model_->getOutsideTemperature(); }
    float getInputPower() const { return model_->getInputPower(); }
    float getFloorArea() const { return model_->getFloorArea(); }
    void setOutsideTemperature(float mean, float range);
    void updateModel(float timeSpanSeconds, timeOfDay tod);
    
};

#endif // CONTROLLER_H
