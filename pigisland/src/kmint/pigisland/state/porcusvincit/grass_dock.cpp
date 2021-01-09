
#include <kmint/astar/astar.hpp>
#include <kmint/pigisland/node_algorithm.hpp>
#include <kmint/random.hpp>
#include "grass_dock.hpp"
#include "wander_state.hpp"

namespace kmint::pigisland {

    void GrassDockState::start(kmint::pigisland::boat *actor) {
        kmint::graph::basic_node<map::map_node_info> &rNode = find_node_of_kind(_g, '2');

        Astar astar(_g, actor->node().node_id(), rNode.node_id());
        astar.search();

        _path = astar.construct_path();
    }

    void GrassDockState::execute(kmint::pigisland::boat *actor, kmint::delta_time dt) {
        actor->node(_g[_path.back()]);
        _path.pop_back();

        if(actor->node().node_info().kind == '2') {
            int repair = random_int(20, 100);
            actor->repair('2', repair);

            std::cout << "Boat has been repaired with: " << repair << std::endl;
            actor->transitionTo(new WanderState(_g));
        }
    }

}
