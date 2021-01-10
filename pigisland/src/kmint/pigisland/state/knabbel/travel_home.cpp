#include <kmint/pigisland/state/state.hpp>
#include <kmint/astar/astar.hpp>
#include <kmint/pigisland/node_algorithm.hpp>
#include <kmint/pigisland/main.hpp>
#include "travel_home.hpp"
#include "wander_state.hpp"

namespace kmint::pigisland::knabbel {
    void TravelHomeState::start(kmint::pigisland::shark *actor) {
        kmint::graph::basic_node<map::map_node_info> &rNode = find_node_of_kind(_g, 'K');

        Astar astar(_g, actor->node().node_id(), rNode.node_id());
        astar.search();

        _path = astar.construct_path();
        actor->canEat = false;
    }

    void TravelHomeState::execute(kmint::pigisland::shark *actor, kmint::delta_time dt) {
        actor->node(_g[_path.back()]);
        _path.pop_back();


        if (actor->node().node_info().kind == 'K') {
            actor->fatigue = 0;

            actor->queuePigs();
            actor->transitionTo(new WanderState(_g));
        }


    }
}