#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {

    pig::pig(math::vector2d location)
            :PhysicsActor(location, drawable_),
              drawable_{*this, pig_image()}  {
        _position = location;
    }

    void pig::act(delta_time dt) {

        this->handle_collisions([this](actor &a) {
            if (auto *boat = dynamic_cast<kmint::pigisland::boat *>(&a)) {
                boat->board(this);
            } else if (auto *shark = dynamic_cast<kmint::pigisland::shark *>(&a)) {
                shark->eat(this);
            }
        });

        if (!this->removed()) {
            vector2d steeringForce = _steeringBehaviour->calculate();


            steeringForce += (_steeringBehaviour->seek(boat_->location()) * _w_boat * 0.1) * 0.001;

            steeringForce += (_steeringBehaviour->seek(shark_->location()) * _w_shark * 0.1) * 0.001;

            vector2d acceleration = steeringForce / mass;
            _velocity += acceleration * dt.count();
            _velocity.truncate(max_speed);

            _position += _velocity * to_seconds(dt);

            location(_position);

            auto length = (_velocity.x() * _velocity.x() + _velocity.y() * _velocity.y());


            if (length > 0.00000001) {
                heading(math::normalize(_velocity));
            }
        }


    }

    pig::~pig() {

    }


} // namespace kmint
