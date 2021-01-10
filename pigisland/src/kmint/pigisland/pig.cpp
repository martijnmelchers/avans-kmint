#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {

    pig::pig(math::vector2d location)
            : PhysicsActor(location, drawable_),
              drawable_{*this, pig_image()} {
    }

    void pig::act(delta_time dt) {
        for (std::size_t i = 0; i < num_colliding_actors(); ++i) {
            auto &a = colliding_actor(i);
            if (boat_ != nullptr && &a == boat_) {
                std::cout << "COLLIDED WITH BOAT!!!" << std::endl;
                this->remove();
            }

            if (shark_ != nullptr && &a == shark_) {
                std::cout << "COLLIDED WITH SHARK!!!" << std::endl;
                this->remove();
            }
        }

    }

} // namespace kmint
