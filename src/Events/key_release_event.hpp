#ifndef _KEY_RELEASE_EVENT_H
#define _KEY_RELEASE_EVENT_H

#include "core/events/event.hpp"
#include <SDL2/SDL_keycode.h>

class KeyReleaseEvent : public Event
{
  public:
    SDL_Keycode symbol;

    KeyReleaseEvent(SDL_Keycode keycode) : symbol(keycode)
    {
    }
};

#endif
