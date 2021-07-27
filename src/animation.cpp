#include "./animation.h"

Animation::Animation(){};

Animation::Animation(
  unsigned int idx,
  unsigned int total_frames,
  unsigned int animation_speed
){
  this->idx = idx;
  this->total_frames = total_frames;
  this->animation_speed = animation_speed;
};
