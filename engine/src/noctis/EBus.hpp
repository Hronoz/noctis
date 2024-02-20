#pragma once

#include "Event.hpp"
#include "logger.hpp"
#include <functional>
#include <map>
#include <vector>

// Event bus class
class EBus
{
  public:
    static EBus &Instance();

    template<class T>
    void publish(T *event);

    void subscribe(EventType eventType, const std::function<void(const Event *)> &eventListener);

    void unsubscribe(EventType eventType, const std::function<void(const Event *)> &eventListener);

    ~EBus()
    {
        eventListeners.clear();
        DEBUG("EBus destructor is called");
    }
    void operator=(EBus const &) = delete;

  private:
    std::map<EventType, std::vector<std::function<void(const Event *)>>> eventListeners;

    EBus() {}
};

void EBus::subscribe(EventType eventType, const std::function<void(const Event *)> &eventListener)
{
    eventListeners[eventType].push_back(eventListener);
    INFO("Event type: %d", static_cast<std::underlying_type<EventType>::type>(eventType));
}

void EBus::unsubscribe(EventType eventType, const std::function<void(const Event *)> &eventListener)
{
    auto &listeners = eventListeners[eventType];
    // std::erase(listeners, eventListener);
}

EBus &EBus::Instance()
{
    static EBus instance;
    return instance;
}

template<class T>
void EBus::publish(T *event)
{
    static_assert(std::is_base_of_v<Event, T> == true);

    for (const auto &listener : eventListeners[event->type]) {
        listener(event);
    }
}