#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "./transform_component.h"
#include "../texture_manager.h"
#include "../asset_manager.h"
#include "../animation.h"

class Sprite_Component : public Component {
  private:
    Transform_Component* transform;
    SDL_Texture* texture;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;
    bool is_animated;
    int total_frames;
    int animation_speed;
    bool is_fixed;
    std::map<std::string, Animation> animations;
    std::string current_animation_name;
    unsigned int animation_idx;

  public:
    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

    Sprite_Component(const char* filename);
    Sprite_Component(
      std::string id,
      int total_frames,
      int animation_speed,
      bool has_directions,
      bool is_fixed
    );

    void play(std::string animation_name);
    void set_texture(std::string asset_texture_id);
    void initialize() override;
    void update(float delta_time) override;
    void render() override;
};

#endif
