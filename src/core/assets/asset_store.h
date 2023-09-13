#ifndef _ASSET_STORE_H
#define _ASSET_STORE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

class AssetStore
{
  private:
    std::map<std::string, SDL_Texture *> m_textures;

  public:
    AssetStore();
    ~AssetStore();

    void clearAssets();
    void addTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath);
    SDL_Texture *getTexture(const std::string &assetId);
};

#endif
