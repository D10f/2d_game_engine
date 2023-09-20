#ifndef _EVENT_BUS_H
#define _EVENT_BUS_H

#include "Logger/Logger.hpp"
#include "core/events/event_callback.hpp"
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <utility>

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus
{
  private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

  public:
    EventBus()
    {
        Logger::log("EventBus constructor called!");
    }

    ~EventBus()
    {
        Logger::log("EventBus destructor called!");
    }

    // Clears the subscribers list
    void Reset()
    {
        subscribers.clear();
    }

    ///////////////////////////////////////////////////////////////////////
    // Subscribe to an event type <T>
    // In our implementation, a listener subscribes to an event
    // Example: eventBus->SubscribeToEvent<CollisionEvent>(this,
    // &Game::onCollision);
    ///////////////////////////////////////////////////////////////////////
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner *ownerInstance, void (TOwner::*callbackFunction)(TEvent &))
    {
        if (!subscribers[typeid(TEvent)].get())
        {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    ///////////////////////////////////////////////////////////////////////
    // Emit an event of type <T>
    // In our implementation, as soon as something emits an
    // event we go ahead and execute all the listener callback functions
    // Example: eventBus->EmitEvent<CollisionEvent>(player, enemy);
    ///////////////////////////////////////////////////////////////////////
    template <typename TEvent, typename... TArgs> void EmitEvent(TArgs &&...args)
    {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers)
        {
            for (auto it = handlers->begin(); it != handlers->end(); it++)
            {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }
};

#endif
