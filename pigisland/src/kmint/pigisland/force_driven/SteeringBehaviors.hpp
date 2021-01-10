#pragma once
#include "kmint/math/vector2d.hpp"
#include "PhysicsActor.hpp"
#include "map"
namespace kmint::pigisland{




    class PhysicsActor;
    using namespace math;

    struct wall{
        vector2d a;
        vector2d b;

        vector2d normal;
    };


    class SteeringBehaviors {
    public:
        SteeringBehaviors(PhysicsActor* actor);
        ~SteeringBehaviors();
        vector2d calculate();
        vector2d seek(vector2d targetPos);

    private:
        PhysicsActor* _actor{};
        std::array<vector2d, 3> _feelers{};
        std::vector<wall> _walls{};
        std::map<rectangle,vector2d > _normals{};
        const int _feeler_length = 30;
        vector2d flee(vector2d targetPos);
        void createWalls();
        vector2d cohesion();
        vector2d wall_avoidance(std::vector<wall> walls);
        vector2d separation();
        vector2d alignment();
        void createFeelers();
        std::vector<std::reference_wrapper<kmint::play::actor>> getNeighbors();
    };

}

inline bool LineIntersection2D(kmint::math::vector2d A,
                               kmint::math::vector2d B,
                               kmint::math::vector2d C,
                               kmint::math::vector2d D,
                               double &dist, kmint::math::vector2d&  point)
{

    double rTop = (A.y()-C.y())*(D.x()-C.x())-(A.x()-C.x())*(D.y()-C.y());
    double sTop = (A.y()-C.y())*(B.x()-A.x())-(A.x()-C.x())*(B.y()-A.y());

    double Bot = (B.x()-A.x())*(D.y()-C.y())-(B.y()-A.y())*(D.x()-C.x());


    if (Bot == 0)//parallel
    {
        if (rTop == 0 && sTop == 0)
        {
            return true;
        }
        return false;
    }

    double r = rTop/Bot;
    double s = sTop/Bot;

    if( (r > 0) && (r < 1) && (s > 0) && (s < 1) )
    {
        dist = kmint::math::distance(A,B) * r;
        point = A + r * (B - A);
        return true;
    }

    else
    {
        dist = 0;

        return false;
    }
}


