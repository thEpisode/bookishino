#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H
#include <string>

namespace EventBus
{
    /**
  @class EventFactory
  @brief Base class for all events
  This class provides the interface that needs to be implemented by an event.
  Each dependent class is required to implement type() to uniquely identify
  events. As a convenience, each class should have a static descriptor so that
  clients may refer to it without having to create an instance.
  Unfortunately, I have no idea how to enforce the existence of this attribute.
*/
    template <typename T>
    class EventFactory
    {
    protected:
        T _type;
        std::string _name;
        bool _handled = false;

    public:
        EventFactory() = default;
        EventFactory(T type, const std::string &name = "") : _type(type), _name(name){};
        inline const T type() const { return _type; };
        inline const std::string &getName() const { return _name; };
        virtual bool isHandled() { return _handled; };

    private:
    };
} // namespace EventBus

#endif