#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {

    pig::pig(math::vector2d location)
            :PhysicsActor(location, drawable_),
              drawable_{*this, pig_image()}  {
    }

    void pig::act(delta_time dt) {
        actor::act(dt);
    }

} // namespace kmint
