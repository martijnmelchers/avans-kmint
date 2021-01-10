#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include <map>
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/state/state.hpp"
#include "pig.hpp"


namespace kmint::pigisland {

    class boat : public play::map_bound_actor, public Context<kmint::pigisland::boat> {
    public:
        boat(map::map_graph &g, map::map_node &initial_node);

        // wordt elke game tick aangeroepen
        void act(delta_time dt) override;

        [[nodiscard]] ui::drawable const &drawable() const override { return drawable_; }

        // als incorporeal false is, doet de actor mee aan collision detection
        [[nodiscard]] bool incorporeal() const override { return false; }

        // geeft de lengte van een zijde van de collision box van deze actor terug.
        // Belangrijk voor collision detection
        [[nodiscard]] scalar collision_range() const override { return 100.0; }

        int paintDamage = 0;

        ~boat();

        // Repair
        std::map<char, std::vector<int>> repairValues;
        void repair(char dock, int repairAmount);

        // Transitions
        void transitionTo(State<boat> *state) override;

        void board(actor *a);

    private:
        // weet hoe de koe getekend moet worden
        play::image_drawable drawable_;

        // hoeveel tijd is verstreken sinds de laatste beweging
        delta_time t_passed_{};

        // De graph
        map::map_graph &_g;
        int savedPigs = 0;
    };

} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
