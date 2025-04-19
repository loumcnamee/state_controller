#include "Controller.h"
#include "HeatingState.h"
#include "CoolingState.h"
#include "IdleState.h"

using std::optional;
using std::unique_ptr;
using std::variant;
using std::visit;
using std::string;

template class Controller<std::variant<IdleState, HeatingState, CoolingState>, std::variant<EventStart, EventTooHot, EventTooCold, EventStop>, Transitions>;

template <typename StateVariant, typename EventVariant, typename Transitions>
Controller<StateVariant, EventVariant, Transitions>::Controller()
{
    model_ = std::make_unique<HomeHeatModel>(HomeHeatModel());
    surfaceTempModel_ = std::make_unique<DiurnalSurfaceTemperatureModel>(DiurnalSurfaceTemperatureModel()) ;
}


template <typename StateVariant, typename EventVariant, typename Transitions>
std::string Controller<StateVariant, EventVariant, Transitions>::getStateName() const
    {
        return std::visit([](auto&& state) { return state.name(); }, m_curr_state);
    }


template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::dispatch(const EventVariant &Event) {
    optional<StateVariant> new_state = visit(Transitions{}, m_curr_state, Event);
    if (new_state) {
        m_curr_state = *move(new_state);
    }
    // Update the model with the new state
    
    model_->setInputPower(std::visit([](auto&& state) { return state.power(); }, m_curr_state));
}


    //template std::variant<IdleState, HeatingState, CoolingState>::name();
template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::updateModel(float timeSpanSeconds, timeOfDay tod) {
    float outside_temp = surfaceTempModel_->compute_surface_temperature(static_cast<float>(tod));
    model_->setOutisdeTemperature(outside_temp);
    model_->compute_temperature(timeSpanSeconds);
    
}

template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::setOutsideTemperature(float mean, float range) {
    surfaceTempModel_->setOutsideTemperature(mean, range);
    model_->setOutisdeTemperature(mean);
}