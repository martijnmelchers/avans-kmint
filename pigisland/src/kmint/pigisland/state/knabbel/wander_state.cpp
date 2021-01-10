#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include <kmint/astar/astar.hpp>
#include <numeric>
#include "wander_state.hpp"
#include "kmint/random.hpp"
#include "travel_home.hpp"
#include "fleeing_boat.hpp"
#include "hunt_pig.hpp"
#include <bits/stdc++.h>
#include <kmint/pigisland/node_algorithm.hpp>

namespace kmint::pigisland::knabbel {
    void WanderState::start(kmint::pigisland::shark *actor) {
        actor->canEat = true;
    }

    void WanderState::execute(kmint::pigisland::shark *actor, kmint::delta_time dt) {
        int next_index = random_int(0, actor->node().num_edges());
        actor->node(actor->node()[next_index].to());

        // Tired let's go home
        if(actor->fatigue++ == 100) {
            actor->transitionTo(new TravelHomeState(_g));
        }

        if(kmint::math::distance(actor->location(), actor->boat_->location()) <= 50.0f) {
            actor->transitionTo(new FleeBoatState(_g));
        }

        for (auto i = actor->begin_perceived(); i != actor->end_perceived(); ++i) {
            std::cout << "smelled pig at " << i->location().x() << " " << i->location().y() << " nodes: " << _g.num_nodes() << std::endl;
            actor->smelledPos = i->location();
            actor->transitionTo(new HuntPigState(_g));
            return;
        }
    }
}