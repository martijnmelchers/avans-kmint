#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>
namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node)
    : play::map_bound_actor{initial_node}, drawable_{*this,
                                                     graphics::image{
                                                         shark_image()}} {}

void shark::act(delta_time dt) {

}

} // namespace pigisland
} // namespace kmint
