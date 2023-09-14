#ifndef _MAP_H
#define _MAP_H

#include "core/ecs/registry.hpp"
#include <algorithm>
#include <string>

class Map
{
  private:
    std::shared_ptr<Registry> m_registry;
    std::string m_mapTexture;

  public:
    Map(std::shared_ptr<Registry> registry, std::string textureId, uint32_t tileSize, double scale);

    ~Map() = default;

    uint32_t m_tileSize;
    uint32_t m_scale;
    uint32_t m_width;
    uint32_t m_height;

    void loadMap(const std::string &filePath, size_t width, size_t height);
};

#endif
