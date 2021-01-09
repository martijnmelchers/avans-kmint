#pragma once
#include "kmint/math/vector2d.hpp"
#include "PhysicsActor.hpp"

namespace kmint::pigisland{
    using namespace math;
    class SteeringBehaviors {
    public:
        SteeringBehaviors(PhysicsActor& actor);
        vector2d calculate();

    private:
        PhysicsActor& _actor;

        vector2d seek(vector2d targetPos);
        vector2d flee(vector2d targetPos);
        vector2d cohesion();
        vector2d wall_avoidance();
        vector2d separation();

        vector2d alignment();
    };
}



