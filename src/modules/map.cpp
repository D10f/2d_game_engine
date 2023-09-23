#include "map.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "core/ecs/entity.hpp"
#include "glm/fwd.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <utility>

size_t Map::m_width = 0;
size_t Map::m_height = 0;

Map::Map(std::shared_ptr<Registry> registry, std::string textureId, uint32_t tileSize, double scale)
    : m_registry(std::move(registry)), m_mapTexture(std::move(textureId)), m_tileSize(tileSize), m_scale(scale)
{
}

void Map::loadMap(const std::string &filePath, size_t cols, size_t rows)
{
    std::fstream tilemap;
    tilemap.open(filePath);

    for (size_t y = 0; y < rows; ++y)
    {
        for (size_t x = 0; x < cols; ++x)
        {
            char c = 0;

            tilemap.get(c);
            uint32_t srcRectY = std::atoi(&c) * m_tileSize;
            tilemap.get(c);
            uint32_t srcRectX = std::atoi(&c) * m_tileSize;
            tilemap.ignore();

            Entity tile = m_registry->createEntity();

            m_registry->addComponent<TransformComponent>(
                tile,
                glm::vec2(static_cast<int>(x) * (m_tileSize * m_scale), static_cast<int>(y) * (m_tileSize * m_scale)),
                glm::vec2(m_scale, m_scale), 0.0);
            m_registry->addComponent<SpriteComponent>(tile, "jungle-tilemap", m_tileSize, m_tileSize, 1, srcRectX,
                                                      srcRectY);
        }
    }

    Map::m_width = cols * m_tileSize * m_scale;
    Map::m_height = rows * m_tileSize * m_scale;

    tilemap.close();
}
