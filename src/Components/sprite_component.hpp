#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <SDL2/SDL_rect.h>
#include <cstdint>
#include <string>
#include <utility>

class SpriteComponent
{
  public:
    std::string m_textureId;
    uint32_t m_width;
    uint32_t m_height;
    SDL_Rect srcRect;

    SpriteComponent(std::string textureId = "", uint32_t width = 64, uint32_t height = 64, uint32_t srcRectX = 0,
                    uint32_t srcRectY = 0)
        : m_textureId(std::move(textureId)), m_width(width), m_height(height)
    {
        srcRect = {static_cast<int>(srcRectX), static_cast<int>(srcRectY), static_cast<int>(m_width),
                   static_cast<int>(m_height)};
    }
};

#endif
