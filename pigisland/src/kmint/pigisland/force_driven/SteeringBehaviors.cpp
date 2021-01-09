#include "SteeringBehaviors.hpp"


namespace kmint::pigisland {
    SteeringBehaviors::SteeringBehaviors(PhysicsActor& actor) : _actor(actor) {}

    vector2d SteeringBehaviors::calculate() {
        vector2d steeringForce;

        steeringForce += cohesion();
        steeringForce += wall_avoidance();
        steeringForce += alignment();
        steeringForce += separation();



        steeringForce.truncate(_actor.max_speed);
        return steeringForce;
    }

    vector2d SteeringBehaviors::seek(vector2d targetPos) {
        vector2d DesiredVelocity = math::normalize(targetPos - _actor.location() )* _actor.max_speed;
        return (DesiredVelocity - _actor.location());
    }

    vector2d SteeringBehaviors::flee(vector2d targetPos) {
        vector2d DesiredVelocity = math::normalize(_actor.location() - targetPos)
                * _actor.max_speed;

        return (DesiredVelocity - _actor.location());
    }

    vector2d SteeringBehaviors::cohesion() {
        vector2d centerOfMass, steeringForce;

        int neighborCount;

        for(auto & neighbour : _actor.getSurrounding()) {
            centerOfMass += neighbour->location();
            neighborCount++;
        }

        centerOfMass /= (double)neighborCount;
        steeringForce = seek(centerOfMass);

        return steeringForce;
    }

    vector2d SteeringBehaviors::wall_avoidance() {
        return vector2d();
    }

    vector2d SteeringBehaviors::alignment() {
        vector2d averageHeading;

        int neighbourCount = 0;

        auto surrounding = _actor.getSurrounding();
        for(auto & neighbour : surrounding) {
            averageHeading += neighbour->heading();
            neighbourCount++;
        }

        averageHeading /= (double)neighbourCount;
        averageHeading -= _actor.heading();

        return averageHeading;
    }

    vector2d SteeringBehaviors::separation() {
        vector2d steeringForce;

        auto surrounding = _actor.getSurrounding();
        for(auto & neighbour : surrounding){
            auto toActor = _actor.location() - neighbour->location();

            steeringForce += math::normalize(toActor) / distance(_actor.location(), toActor);
        }

        return steeringForce;
    }

}