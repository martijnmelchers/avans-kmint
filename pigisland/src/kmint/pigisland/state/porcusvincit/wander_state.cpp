#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include "wander_state.hpp"
#include "kmint/random.hpp"

namespace kmint::pigisland {
    void WanderState::start(kmint::pigisland::boat *actor) {

    }

    void WanderState::execute(boat *actor, kmint::delta_time dt) {
        // do shi here

        // pick random edge

        int next_index = random_int(0, actor->node().num_edges());
        actor->node(actor->node()[next_index].to());
        std::cout << "WanderState executed" << std::endl;

    }
}