#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include <kmint/astar/astar.hpp>
#include <numeric>
#include "wander_state.hpp"
#include "kmint/random.hpp"
#include "travel_home.hpp"
#include <bits/stdc++.h>

namespace kmint::pigisland::knabbel {
    void WanderState::start(kmint::pigisland::shark *actor) {

    }

    void WanderState::execute(kmint::pigisland::shark *actor, kmint::delta_time dt) {
        if (_path.empty()) {
            int next_index = random_int(0, _g.num_nodes());

            while (_g[next_index].node_info().kind != 'W' && _g[next_index].node_info().kind != 'R') {
                next_index = random_int(0, actor->node().num_edges());
            }

            kmint::graph::basic_node<map::map_node_info> &rNode = _g[next_index];

            Astar astar(_g, actor->node().node_id(), rNode.node_id());
            astar.search();
            _path = astar.construct_path();
        }

        actor->node(_g[_path.back()]);
        _path.pop_back();

        // Tired let's go home
        if(actor->fatigue++ == 100) {
            std::cout << "I'm tired, let's go home" << std::endl;
            actor->transitionTo(new TravelHomeState(_g));
        }
    }
}