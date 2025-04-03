#include "Controller.h"
#include "HeatingState.h"
#include "CoolingState.h"
#include "IdleState.h"


template class Controller<std::variant<IdleState, HeatingState, CoolingState>, std::variant<EventStart, EventTooHot, EventTooCold, EventStop>, Transitions>;

template <typename StateVariant, typename EventVariant, typename Transitions>
Controller<StateVariant, EventVariant, Transitions>::Controller()
{
    model_ = std::unique_ptr<HomeHeatModel>(new HomeHeatModel());
    surfaceTempModel_ = std::unique_ptr<DiurnalSurfaceTemperatureModel>(new DiurnalSurfaceTemperatureModel()) ;
}


template <typename StateVariant, typename EventVariant, typename Transitions>
std::string Controller<StateVariant, EventVariant, Transitions>::getStateName() const
    {
        return std::visit([](auto&& state) { return state.name(); }, m_curr_state);
    }


template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::dispatch(const EventVariant &Event) {
    optional<StateVariant> new_state = visit(Transitions{}, m_curr_state, Event);
    if (new_state)
        m_curr_state = *move(new_state);
    
    model_->setInputPower(std::visit([](auto&& state) { return state.power(); }, m_curr_state));
}


    //template std::variant<IdleState, HeatingState, CoolingState>::name();


template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::updateModel(float dt, float time_of_day) {
    
    float outside_temp = surfaceTempModel_->compute_surface_temperature(time_of_day);
    model_->setOutisdeTemperature(outside_temp);
    model_->compute_temperature(dt);
    return;
}   

template <typename StateVariant, typename EventVariant, typename Transitions>
void Controller<StateVariant, EventVariant, Transitions>::setOutsideTemperature(float mean, float range) {
    surfaceTempModel_->setOutsideTemperature(mean, range);
    model_->setOutisdeTemperature(mean);
    return;
}