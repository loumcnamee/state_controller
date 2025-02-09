#include "Controller.h"
#include "HeatingState.h"
#include "CoolingState.h"
#include "IdleState.h"


template <typename StateVariant, typename EventVariant, typename Transitions>
Controller<StateVariant, EventVariant, Transitions>::Controller()
{
    model_ = std::unique_ptr<HomeHeatModel>(new HomeHeatModel());

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
}

    template class Controller<std::variant<IdleState, HeatingState, CoolingState>, std::variant<EventStart, EventTooHot, EventTooCold, EventStop>, Transitions>;
    //template std::variant<IdleState, HeatingState, CoolingState>::name();
