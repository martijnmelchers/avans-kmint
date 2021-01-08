#include <kmint/astar/astar.hpp>
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
namespace kmint {
namespace pigisland {
  boat::boat(map::map_graph& g, map::map_node& initial_node)
    : play::map_bound_actor{ initial_node },
      drawable_{ *this, graphics::image{boat_image()} }, _g(g) {}


  void boat::act(delta_time dt) {
    t_passed_ += dt;
    if (to_seconds(t_passed_) >= 1) {
      // pick random edge

      if(_path.empty()){
          int next_index = random_int(0, _g.num_nodes());

          while(_g[next_index].node_info().kind != 'W' && _g[next_index].node_info().kind != 'R'){
              next_index = random_int(0, node().num_edges());
          }

          kmint::graph::basic_node<map::map_node_info>& rNode = _g[next_index];

          Astar astar(_g,node().node_id(),rNode.node_id());
          astar.search();
          _path = astar.construct_path();
      }


      int path_id = _path.back();
      this->node(_g[path_id]);
      _path.pop_back();

      t_passed_ = from_seconds(0);
    }
  }



} // namespace pigisland
} // namespace kmint
