#include "./sprite_component.h"

Sprite_Component::Sprite_Component(const char* filename) {
  is_animated = false;
  is_fixed = false;
  set_texture(filename);
}

Sprite_Component::Sprite_Component(
  std::string id,
  int total_frames,
  int animation_speed,
  bool has_directions,
  bool is_fixed
) {
  is_animated = true;
  this->total_frames = total_frames;
  this->animation_speed = animation_speed;
  this->is_fixed = is_fixed;

  if (has_directions) {
    // Entities that can move and turn have an animation for each direction
    Animation down_animation  = Animation(0, total_frames, animation_speed);
    Animation right_animation = Animation(1, total_frames, animation_speed);
    Animation left_animation  = Animation(2, total_frames, animation_speed);
    Animation up_animation    = Animation(3, total_frames, animation_speed);

    // After they are created, add them to the sprite component list
    animations.emplace("down_animation",  down_animation);
    animations.emplace("right_animation", right_animation);
    animations.emplace("left_animation",  left_animation);
    animations.emplace("up_animation",    up_animation);

    // Arbitrarily choose a starting frame idx and direction
    this->animation_idx = 0;
    this->current_animation_name = "down_animation";

  } else {
    // Only one "static animation" is required for entities that won't turn
    Animation single_animation = Animation(0, total_frames, animation_speed);
    animations.emplace("single_animation", single_animation);
    this->animation_idx = 0;
    this->current_animation_name = "single_animation";
  }

  play(current_animation_name);
  set_texture(id);
}

void Sprite_Component::play(std::string animation_name) {
  total_frames  = animations[animation_name].total_frames;
  animation_speed = animations[animation_name].animation_speed;
  current_animation_name = animation_name;
}

void Sprite_Component::set_texture(std::string asset_texture_id) {
  texture = Game::asset_manager->get_texture(asset_texture_id);
}

void Sprite_Component::initialize() {
  transform = owner->get_component<Transform_Component>();
  source_rect.x = 0;
  source_rect.y = 0;
  source_rect.w = transform->width;
  source_rect.h = transform->height;
}

void Sprite_Component::update(float delta_time) {
  if (is_animated) {
    source_rect.x = source_rect.w * static_cast<int>((SDL_GetTicks() / animation_speed) % total_frames);
  }
  source_rect.y = animation_idx * transform->height;

  dest_rect.x = static_cast<int>(transform->pos.x);
  dest_rect.y = static_cast<int>(transform->pos.y);
  dest_rect.w = transform->width * transform->scale;
  dest_rect.h = transform->height * transform->scale;
}

void Sprite_Component::render() {
  Texture_Manager::draw(texture, source_rect, dest_rect, sprite_flip);
}
