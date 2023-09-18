#ifndef _EVENT_CALLBACK_H
#define _EVENT_CALLBACK_H

#include <core/events/event.hpp>
#include <functional>

class IEventCallback
{
  private:
    virtual void call(const Event &event) = 0;

  public:
    virtual ~IEventCallback() = default;
    void execute(const Event &event)
    {
        call(event);
    }
};

template <typename TOwner, typename TEvent> class EventCallback : public IEventCallback
{
  private:
    using CallbackFunction = void (TOwner::*)(Event &);

    TOwner *m_ownerInstance;
    CallbackFunction m_callbackFunction;

    void call(const Event &event) override
    {
        std::invoke(m_callbackFunction, m_ownerInstance, static_cast<TEvent &>(event));
    }

  public:
    EventCallback(TOwner *ownerInstance, CallbackFunction callbackFunction)
        : m_ownerInstance(ownerInstance), m_callbackFunction(callbackFunction)
    {
    }

    ~EventCallback() override = default;
};

#endif
