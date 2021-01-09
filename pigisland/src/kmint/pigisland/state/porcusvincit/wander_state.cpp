#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include "wander_state.hpp"
#include "kmint/random.hpp"

namespace kmint::pigisland {
    void WanderState::start(kmint::pigisland::boat  *actor) {

    }

    void WanderState::execute(boat *actor, kmint::delta_time dt) {
        // do shi here
        actor->t_passed_ += dt;
        if (to_seconds(actor->t_passed_) >= 1) {
            // pick random edge
            int next_index = random_int(0, actor->node().num_edges());
            actor->node(actor->node()[next_index].to());
            actor->t_passed_ = from_seconds(0);

            std::cout << "WanderState executed" << std::endl;
        }
    }

    WanderState::WanderState(map::map_graph &g): _g(g){
    }
}