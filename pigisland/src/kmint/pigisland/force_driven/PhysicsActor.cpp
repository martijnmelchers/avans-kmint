//
// Created by sasch on 09/01/2021.
//

#include <kmint/random.hpp>
#include <kmint/map/map.hpp>

#include "PhysicsActor.hpp"
#include "memory"

namespace kmint::pigisland {
    using namespace math;

    PhysicsActor::PhysicsActor(math::vector2d location, ui::drawable& drawable) : free_roaming_actor(location, drawable), _drawable(drawable) {
        _steeringBehaviour = new SteeringBehaviors(this);

        randomWeights();
    }

    const ui::drawable &PhysicsActor::drawable() const {
        return _drawable;
    }

    vector2d PhysicsActor::get_velocity() {
        return _velocity;
    }

    void PhysicsActor::randomWeights() {
        _cohesion   = random_scalar(0.0f, 1.0f);
        _separation = random_scalar(0.0f, 1.0f);
        _alignment  = random_scalar(0.0f, 1.0f);

        _w_boat   = random_scalar(-1.0f, 1.0f);
        _w_shark = random_scalar(-1.0f, 1.0f);
    }
}
