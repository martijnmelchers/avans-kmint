#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "boat.hpp"
#include "shark.hpp"
#include <tuple>
#include <vector>
#include <kmint/pigisland/force_driven/PhysicsActor.hpp>

namespace kmint::pigisland {
        using namespace  kmint::math;
        class pig : public PhysicsActor  {
        public:
            pig(vector2d location);
            [[nodiscard]] const ui::drawable &drawable() const override { return drawable_; }
            // geeft aan dat de haai andere actors kan zien
            [[nodiscard]] bool perceptive() const override { return true; }

            // geeft het bereik aan waarbinnen een haai
            // andere actors kan waarnemen.
            [[nodiscard]] scalar perception_range() const override { return 50.f; }
            [[nodiscard]] bool incorporeal() const override { return false; }
            [[nodiscard]] scalar collision_range() const override { return 16.0; }

            void setBoat(boat const &c) { boat_ = &c; }
            void setShark(shark const &c) { shark_ = &c; }


        private:
            play::image_drawable drawable_;
            void act(delta_time dt) override;

            boat const *boat_{};
            shark const *shark_{};

        };

    } // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
