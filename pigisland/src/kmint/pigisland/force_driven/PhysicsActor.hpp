#pragma once

#include <kmint/math/vector2d.hpp>

namespace kmint {
    namespace pigisland {
    using namespace math;

    class PhysicsActor {
        private:
            const double mass = 0;
            // Applied force.
            vector2d force{};

            // Acceleration: force / mass
            vector2d velocity{};

            // Calculated position: position() (current) + velocity * deltaTime
            vector2d position{};


        public:
            vector2d seek(vector2d targetPos);
            void pursuit();
            void wander();

            void set_acceleration(double a);

            void set_velocity(double v);

            void set_position(double dV);
        };

    }
}
