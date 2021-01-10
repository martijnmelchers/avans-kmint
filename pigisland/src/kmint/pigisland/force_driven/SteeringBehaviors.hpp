#pragma once
#include "kmint/math/vector2d.hpp"
#include "PhysicsActor.hpp"

namespace kmint::pigisland{
    class PhysicsActor;
    using namespace math;
    class SteeringBehaviors {
    public:
        SteeringBehaviors(PhysicsActor* actor);
        ~SteeringBehaviors();
        vector2d calculate();
        vector2d seek(vector2d targetPos);

    private:
        PhysicsActor* _actor{};
        std::vector<vector2d> _feelers{};
        const int _feeler_length = 30;
        vector2d flee(vector2d targetPos);
        vector2d cohesion();
        vector2d wall_avoidance();
        vector2d separation();
        vector2d alignment();
        void createFeelers();
        std::vector<std::reference_wrapper<kmint::play::actor>> getNeighbors();
    };

}



