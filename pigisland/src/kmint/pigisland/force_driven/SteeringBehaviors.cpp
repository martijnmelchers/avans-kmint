#include <iostream>
#include "SteeringBehaviors.hpp"
#include "math.h"

namespace kmint::pigisland {
    SteeringBehaviors::SteeringBehaviors(PhysicsActor* actor) : _actor(actor) {}

    vector2d SteeringBehaviors::calculate() {
        vector2d steeringForce;

        steeringForce += cohesion() * 0.001;
        steeringForce += wall_avoidance();
        steeringForce += alignment();
        steeringForce += separation();



        steeringForce.truncate(_actor->max_speed);
        return steeringForce;
    }

    vector2d SteeringBehaviors::seek(vector2d targetPos) {
        vector2d DesiredVelocity = math::normalize(targetPos - _actor->location() )* _actor->max_speed;
        return (DesiredVelocity - _actor->location());
    }

    vector2d SteeringBehaviors::flee(vector2d targetPos) {
        vector2d DesiredVelocity = math::normalize(_actor->location() - targetPos)
                * _actor->max_speed;

        return (DesiredVelocity - _actor->location());
    }

    vector2d SteeringBehaviors::cohesion() {
        vector2d centerOfMass, steeringForce;

        int neighborCount = 0;

        for(auto & neighbour : getNeighbors()) {
            centerOfMass += neighbour.get().location();
            neighborCount++;
        }

        if(neighborCount > 0){
            centerOfMass /= (double)neighborCount;
            steeringForce = seek(centerOfMass);
        }

        return steeringForce;
    }

    vector2d SteeringBehaviors::wall_avoidance() {
        createFeelers();


        double distToThisIntersection = 0.0;
        double distToClosestIntersection = INFINITY;

        int closestWall = -1;


        vector2d steeringForce,
                 point, //used for storing temporary info
                 closestPoint;  //holds the closest intersection point


        return vector2d();
    }

    vector2d SteeringBehaviors::alignment() {
        vector2d averageHeading;

        int neighbourCount = 0;

        auto surrounding = getNeighbors();
        for(auto & neighbour : surrounding) {
            averageHeading += neighbour.get().heading();
            neighbourCount++;
        }


        if(neighbourCount > 0){
            averageHeading /= (double)neighbourCount;

        }
        averageHeading -= _actor->heading();

        return averageHeading;
    }

    vector2d SteeringBehaviors::separation() {
        vector2d steeringForce;

        auto surrounding = getNeighbors();
        for(auto & neighbour : surrounding){
            auto toActor = _actor->location() - neighbour.get().location();

            steeringForce += math::normalize(toActor) / distance(_actor->location(), toActor);
        }


        return steeringForce;
    }

    void SteeringBehaviors::createFeelers() {

        return;
        _feelers[0] = _actor->location() + _feeler_length * _actor->heading();

        vector2d temp = _actor->heading();
        auto angle = math::angle::from_degrees(M_PI_2 * 3.5f);
        temp = math::rotate(temp,angle);
        _feelers[1] = _actor->location() + _feeler_length / 2 * temp;


        temp = _actor->heading();
        angle = math::angle::from_degrees(M_PI_2 * 0.5f);
        temp = math::rotate(temp,angle);
        _feelers[2] = _actor->location() + _feeler_length / 2 * temp;
    }

    std::vector<std::reference_wrapper<kmint::play::actor>> SteeringBehaviors::getNeighbors() {
        std::vector<std::reference_wrapper<kmint::play::actor>> perceived{};
        for (auto i = _actor->begin_perceived(); i != _actor->end_perceived(); ++i) {
            play::actor& actor = *i;

            perceived.emplace_back(actor);
        }

        return perceived;
    }

    SteeringBehaviors::~SteeringBehaviors() {
        //delete _actor;
    }


}