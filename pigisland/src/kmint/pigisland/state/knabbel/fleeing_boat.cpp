#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/main.hpp>
#include <kmint/random.hpp>
#include "fleeing_boat.hpp"
#include "wander_state.hpp"

namespace kmint::pigisland::knabbel {
    void FleeBoatState::start(kmint::pigisland::shark *actor) {
        actor->canEat = false;
    }

    void FleeBoatState::execute(kmint::pigisland::shark *actor, kmint::delta_time dt) {
        if(remainingFlees-- >= 0) {
            int next_index = random_int(0, actor->node().num_edges());
            actor->node(actor->node()[next_index].to());
        } else {
            actor->transitionTo(new WanderState(_g));
        }




    }
}