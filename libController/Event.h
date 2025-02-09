#ifndef EVENT_H
#define EVENT_H


#include <variant>


// Eveents that trigger state transitions
struct EventStart { };
struct EventTooHot { };
struct EventTooCold { };
struct EventStop { };

using Event = std::variant<EventStart, EventTooHot, EventTooCold, EventStop>;


#endif // EVENT_H