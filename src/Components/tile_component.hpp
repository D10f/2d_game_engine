#ifndef _TILE_COMPONENT_H
#define _TILE_COMPONENT_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <utility>

class TileComponent
{
  public:
    std::string m_textureId;
    uint32_t m_width;
    uint32_t m_height;
    SDL_Rect m_srcRect;

    TileComponent(std::string textureId = {}, uint32_t srcRectX = 0, uint32_t srcRectY = 0, uint32_t tileSize = 0,
                  uint32_t scale = 0)
        : m_textureId(std::move(textureId)), m_width(tileSize), m_height(tileSize)
    {
        m_srcRect = {static_cast<int>(srcRectX), static_cast<int>(srcRectY), static_cast<int>(m_width),
                     static_cast<int>(m_height)};
    };
};

#endif
