
#include <kmint/astar/astar.hpp>
#include <kmint/pigisland/node_algorithm.hpp>
#include <kmint/random.hpp>
#include "grain_dock.hpp"
#include "wander_state.hpp"

namespace kmint::pigisland::pv {

    void GrainDockState::start(kmint::pigisland::boat *actor) {
        kmint::graph::basic_node<map::map_node_info> &rNode = find_node_of_kind(_g, '1');

        Astar astar(_g, actor->node().node_id(), rNode.node_id());
        astar.search();

        _path = astar.construct_path();
    }

    void GrainDockState::execute(kmint::pigisland::boat *actor, kmint::delta_time dt) {
        actor->node(_g[_path.back()]);
        _path.pop_back();

        if(actor->node().node_info().kind == '1') {
            int repair = random_int(30, 50);
            actor->repair('1', repair);

            std::cout << "Boat has been repaired with: " << repair << std::endl;
            actor->transitionTo(new WanderState(_g));
        }
    }

}
