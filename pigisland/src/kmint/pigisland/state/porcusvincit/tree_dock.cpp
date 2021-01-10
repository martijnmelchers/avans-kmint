
#include <kmint/astar/astar.hpp>
#include <kmint/pigisland/node_algorithm.hpp>
#include <kmint/random.hpp>
#include "tree_dock.hpp"
#include "wander_state.hpp"

namespace kmint::pigisland::pv {

    void TreeDockState::start(kmint::pigisland::boat *actor) {
        kmint::graph::basic_node<map::map_node_info> &rNode = find_node_of_kind(_g, '3');

        Astar astar(_g, actor->node().node_id(), rNode.node_id());
        astar.search();
        play::image_drawable& image = (kmint::play::image_drawable& ) actor->drawable();
        image.set_tint(graphics::color(100,0,0));

        _path = astar.construct_path();
        astar.draw_path(_path);
    }

    void TreeDockState::execute(kmint::pigisland::boat *actor, kmint::delta_time dt) {
        actor->node(_g[_path.back()]);
        _path.pop_back();

        if(actor->node().node_info().kind == '3') {
            int repair = 50;
            actor->repair('3', repair);

            std::cout << "Boat has been repaired with: " << repair << std::endl;
            actor->transitionTo(new WanderState(_g));
        }
    }

}
