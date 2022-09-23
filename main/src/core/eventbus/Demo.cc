#include "contracts/api.contract.h"
#include "Dispatcher.h"

#include <functional>
#include <iostream>

void onEvent(const EventBus::EventFactory<EventBus::EventTypes> &event)
{
    if (event.type() == EventBus::EventTypes::DEFAULT)
    {
        std::cout << "Function Event TYPE: EventTypes::TEST_EVENT " << event.getName() << std::endl;
    }
}

int main(int, char **)
{
    EventBus::Dispatcher<EventBus::EventTypes> dispatcher;

    // Subscribe to event
    dispatcher.subscribe(EventBus::EventTypes::DEFAULT, onEvent);

    // Create new instance of event
    EventBus::ApiEvent event(EventBus::EventTypes::DEFAULT, "Default Event");

    // Emit event
    dispatcher.emit(event);

    return 0;
}