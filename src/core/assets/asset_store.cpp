#include "core/assets/asset_store.h"
#include "Logger/Logger.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

AssetStore::AssetStore()
{
    Logger::log("Asset store constructor");
}

AssetStore::~AssetStore()
{
    clearAssets();
    Logger::log("Asset store destructor");
}

void AssetStore::addTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath)
{
    /* SDL_Surface *surface = IMG_Load(filePath.c_str()); */
    /* SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); */
    /* SDL_FreeSurface(surface); */
    SDL_Texture *texture = IMG_LoadTexture(renderer, filePath.c_str());
    m_textures.emplace(assetId, texture);
    Logger::log("New texture added with id: " + assetId);
}

SDL_Texture *AssetStore::getTexture(const std::string &assetId)
{
    return m_textures[assetId];
}

void AssetStore::clearAssets()
{
    for (const auto &texture : m_textures)
    {
        SDL_DestroyTexture(texture.second);
    }

    m_textures.clear();
}
