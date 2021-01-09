#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor {
public:
  free_roaming_actor(math::vector2d location, ui::drawable& drawable) : actor{}, _drawable(drawable), location_{location}  {}
  math::vector2d location() const override { return location_; };
const ui::drawable &drawable() const override {return _drawable;}

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  ui::drawable& _drawable;
  math::vector2d location_;
};
} // namespace kmint::play

#endif
