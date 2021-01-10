#pragma once

#include <kmint/math/vector2d.hpp>
#include <kmint/play/actor.hpp>
#include <kmint/play/free_roaming_actor.hpp>
#include "memory"
#include "SteeringBehaviors.hpp"

namespace kmint {
    namespace pigisland {

        class SteeringBehaviors;
    using namespace math;

    class PhysicsActor : public kmint::play::free_roaming_actor {
        private:
            // Acceleration: force / mass
            ui::drawable& _drawable;
    protected:
        const double mass = 10;
        vector2d _velocity = vector2d(0,0);
        vector2d _position = vector2d(0,0);
        vector2d _heading = vector2d(0,0);
        SteeringBehaviors* _steeringBehaviour;
    public:
            explicit PhysicsActor(math::vector2d location, ui::drawable& drawable);
            const double max_speed = 15;
            vector2d get_velocity();
            const ui::drawable &drawable() const override;
            math::vector2d heading() { return _heading; }
            void heading(vector2d heading) { _heading = heading; }
    };
    }
}
