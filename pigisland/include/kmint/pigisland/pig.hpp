#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include <kmint/pigisland/force_driven/PhysicsActor.hpp>

namespace kmint::pigisland {
        using namespace  kmint::math;
        class pig : public PhysicsActor {
        public:
            pig(vector2d location);
            [[nodiscard]] const ui::drawable &drawable() const override { return drawable_; }

        private:
            play::image_drawable drawable_;
            void act(delta_time dt) override;
        };

    } // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
