#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
    unsigned int idx{};
    unsigned int total_frames{};
    unsigned int animation_speed{};

    Animation();
    Animation(
      unsigned int idx,
      unsigned int total_frames,
      unsigned int animation_speed
    );
};

#endif
