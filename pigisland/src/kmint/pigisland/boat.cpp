#include <kmint/pigisland/state/porcusvincit/wander_state.hpp>
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint::pigisland {
        boat::boat(map::map_graph &g, map::map_node &initial_node)
                : play::map_bound_actor{initial_node},
                  drawable_{*this, graphics::image{boat_image()}}, _g(g) {

        }



        void boat::act(delta_time dt) {
            auto state = WanderState(_g);
            state.execute(this, dt);
            // state->update(...);
        }

    boat::~boat() {
    }

} // namespace kmint
