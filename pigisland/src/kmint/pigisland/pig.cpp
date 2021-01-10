#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {

    pig::pig(math::vector2d location)
            : PhysicsActor(location, drawable_),
              drawable_{*this, pig_image()} {
    }

    void pig::act(delta_time dt) {
        this->handle_collisions([this](actor &a) {
            if (auto *boat = dynamic_cast<kmint::pigisland::boat *>(&a)) {
                std::cout << "COLLIDED WITH BOAT!!!" << std::endl;
                this->remove();
            } else if (auto *shark = dynamic_cast<kmint::pigisland::shark *>(&a)) {
                std::cout << "COLLIDED WITH SHARK!!!" << std::endl;
                this->remove();
            }
        });
    }

} // namespace kmint
