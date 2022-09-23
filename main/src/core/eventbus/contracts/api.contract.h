#ifndef API_CONTRACT_H
#define API_CONTRACT_H

#include "../constants/types.h"
#include "../factory/event.factory.h"

namespace EventBus
{
    class ApiEvent : public EventFactory<EventTypes>
    {
    public:
        ApiEvent() = default;
        ApiEvent(EventTypes type, std::string name) : EventFactory<EventTypes>(type, name) {}
        virtual ~ApiEvent() = default;
    };
} // namespace EventBus

#endif