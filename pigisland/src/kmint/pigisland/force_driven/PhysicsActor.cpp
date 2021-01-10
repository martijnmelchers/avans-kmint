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
    }

    const ui::drawable &PhysicsActor::drawable() const {
        return _drawable;
    }

    vector2d PhysicsActor::get_velocity() {
        return _velocity;
    }

    PhysicsActor::~PhysicsActor() {
        play::free_roaming_actor::~free_roaming_actor();

        delete _steeringBehaviour;
    }

}
