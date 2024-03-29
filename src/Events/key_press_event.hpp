#ifndef _KEY_PRESS_EVENT_H
#define _KEY_PRESS_EVENT_H

#include "core/events/event.hpp"
#include <SDL2/SDL_keycode.h>

class KeyPressEvent : public Event
{
  public:
    SDL_Keycode symbol;

    KeyPressEvent(SDL_Keycode keycode) : symbol(keycode)
    {
    }
};

#endif
