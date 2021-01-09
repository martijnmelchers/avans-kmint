#pragma once

#include <kmint/math/vector2d.hpp>
#include <kmint/play/actor.hpp>
#include <kmint/play/free_roaming_actor.hpp>

namespace kmint {
    namespace pigisland {
    using namespace math;

    class PhysicsActor : public kmint::play::free_roaming_actor {
        private:
            const double mass = 0;
            // Acceleration: force / mass
            vector2d _velocity{};
            std::vector<const kmint::play::actor*> _surrounding;
            ui::drawable& _drawable;
        public:
            explicit PhysicsActor(math::vector2d location, ui::drawable& drawable);
            const double max_speed = 100;
            void set_velocity(vector2d velocity);
            void update_surrounding();
            std::vector<const kmint::play::actor*> getSurrounding();
            const ui::drawable &drawable() const override;

    };
    }
}
