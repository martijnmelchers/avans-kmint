#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {

    pig::pig(math::vector2d location)
            :PhysicsActor(location, drawable_),
              drawable_{*this, pig_image()}  {
        _position = location;
    }

    void pig::act(delta_time dt) {

        actor::act(dt);
        update_surrounding();

        vector2d steeringForce  = _steeringBehaviour->calculate();
        vector2d acceleration = steeringForce / mass;
        _velocity += acceleration * dt.count();
        _velocity.truncate(max_speed);

        _position += _velocity * to_seconds(dt);

        location(_position);

        auto length = (_velocity.x() * _velocity.x() + _velocity.y() * _velocity.y());


        if(length > 0.00000001){
            heading(math::normalize(_velocity));
        }
    }

} // namespace kmint
