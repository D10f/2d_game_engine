#ifndef _EVENT_BUS_H
#define _EVENT_BUS_H

#include "core/events/event_callback.hpp"
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <utility>

using HandlerList = std::list<std::unique_ptr<IEventCallback>>;

class EventBus
{
  private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> m_subscribers;

  public:
    EventBus() = default;
    ~EventBus() = default;

    template <typename TOwner, typename TEvent> void subscribe(TOwner *ownerInstance, const TEvent &event);

    template <typename TEvent, typename... TArgs> void emit(TArgs &&...args);
};

template <typename TOwner, typename TEvent> void EventBus::subscribe(TOwner *ownerInstance, const TEvent &event)
{
    if (!m_subscribers[typeid(TEvent)].get())
        m_subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();

    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, event);
    m_subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
}

template <typename TEvent, typename... TArgs> void EventBus::emit(TArgs &&...args)
{
    auto *subscribers = m_subscribers[typeid(TEvent)].get();

    if (!subscribers)
        return;

    // Construct the event before the loop to ensure consistency.
    TEvent event(std::forward<TArgs>(args)...);

    for (const auto &subscriber : *subscribers)
    {
        auto *handler = subscriber.get();
        handler->execute(event);
    }
}

#endif
