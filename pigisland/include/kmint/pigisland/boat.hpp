#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/state/state.hpp"


namespace kmint {
    namespace pigisland {

        class boat : public play::map_bound_actor {
        public:
            boat(map::map_graph &g, map::map_node &initial_node);

            // wordt elke game tick aangeroepen
            void act(delta_time dt) override;

            ui::drawable const &drawable() const override { return drawable_; }

            // als incorporeal false is, doet de actor mee aan collision detection
            bool incorporeal() const override { return false; }

            // geeft de lengte van een zijde van de collision box van deze actor terug.
            // Belangrijk voor collision detection
            scalar collision_range() const override { return 16.0; }

            int paintDamage = 0;
            // hoeveel tijd is verstreken sinds de laatste beweging
            delta_time t_passed_{};

            ~boat();

        private:
            // weet hoe de koe getekend moet worden
            play::image_drawable drawable_;

            // De graph
            map::map_graph &_g;

            // State
            State<kmint::pigisland::boat> *_state{};
        };

    } // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
