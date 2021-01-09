#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include <kmint/astar/astar.hpp>
#include "wander_state.hpp"
#include "kmint/random.hpp"

namespace kmint::pigisland {
    void WanderState::start(kmint::pigisland::boat *actor) {

    }

    void WanderState::execute(boat *actor, kmint::delta_time dt) {
        if(_path.empty()){
            int next_index = random_int(0, _g.num_nodes());

            while(_g[next_index].node_info().kind != 'W' && _g[next_index].node_info().kind != 'R'){
                next_index = random_int(0, actor->node().num_edges());
            }

            kmint::graph::basic_node<map::map_node_info>& rNode = _g[next_index];

            Astar astar(_g,actor->node().node_id(),rNode.node_id());
            astar.search();
            _path = astar.construct_path();
        }


        int path_id = _path.back();
        actor->node(_g[path_id]);
        _path.pop_back();
    }
}