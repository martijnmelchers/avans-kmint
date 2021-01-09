//
// Created by sasch on 09/01/2021.
//

#include <kmint/random.hpp>
#include <kmint/map/map.hpp>

#include "PhysicsActor.hpp"


namespace kmint::pigisland {
    using namespace math;


    void PhysicsActor::set_velocity(vector2d velocity) {
        _velocity = velocity;
    }

    void PhysicsActor::update_surrounding() {
        for (auto i = begin_perceived(); i != end_perceived(); ++i) {
            auto const &a = *i;
            _surrounding.push_back(&a);
        }
    }

    std::vector<const kmint::play::actor *> PhysicsActor::getSurrounding() {
        return _surrounding;
    }

    PhysicsActor::PhysicsActor(math::vector2d location, ui::drawable& drawable) : free_roaming_actor(location, drawable), _drawable(drawable) {}

    const ui::drawable &PhysicsActor::drawable() const {
        return _drawable;
    }
}
