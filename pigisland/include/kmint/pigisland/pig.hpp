#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include <kmint/pigisland/force_driven/PhysicsActor.hpp>

namespace kmint {
    namespace pigisland {
        using namespace  kmint::math;
        class pig : public play::free_roaming_actor, public PhysicsActor {
        public:
            pig(vector2d location);

            const ui::drawable &drawable() const override { return drawable_; }


        private:
            play::image_drawable drawable_;
            double mass;



        };

    } // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
