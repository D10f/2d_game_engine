#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <cstdint>

class SpriteComponent
{
  public:
    uint32_t m_width;
    uint32_t m_height;

    SpriteComponent(uint32_t width, uint32_t height) : m_width(width), m_height(height)
    {
    }
};

#endif
