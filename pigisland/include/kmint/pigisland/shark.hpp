#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/state/state.hpp"
#include "boat.hpp"


namespace kmint::pigisland {
    class shark : public play::map_bound_actor, public Context<kmint::pigisland::shark> {
    public:
        shark(map::map_graph &g, map::map_node &initial_node, play::stage &stage);

        // wordt elke game tick aangeroepen
        void act(delta_time dt) override;

        [[nodiscard]] ui::drawable const &drawable() const override { return drawable_; }

        // als incorporeal false is, doet de actor mee aan collision detection
        [[nodiscard]] bool incorporeal() const override { return false; }

        // geeft de lengte van een zijde van de collision box van deze actor terug.
        // Belangrijk voor collision detection
        [[nodiscard]] scalar collision_range() const override { return 16.0; }

        // geeft aan dat de haai andere actors kan zien
        [[nodiscard]] bool perceptive() const override { return true; }

        // geeft het bereik aan waarbinnen een haai
        // andere actors kan waarnemen.
        [[nodiscard]] scalar perception_range() const override { return 200.f; }

        void queuePigs();
        void transitionTo(State<shark> *state) override;
        void setBoat(boat const &c) { boat_ = &c; }


        int fatigue = 0;
        play::stage &stage;
    private:
        // hoeveel tijd is verstreken sinds de laatste beweging
        delta_time t_passed_{};
        // weet hoe de koe getekend moet worden
        play::image_drawable drawable_;

        boat const *boat_{};


    };

} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
