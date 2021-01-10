#include <kmint/pigisland/state/state.hpp>
#include <kmint/astar/astar.hpp>
#include <kmint/pigisland/node_algorithm.hpp>
#include <kmint/pigisland/main.hpp>
#include <kmint/random.hpp>
#include "wander_state.hpp"
#include "hunt_pig.hpp"
#include "travel_home.hpp"
#include "fleeing_boat.hpp"

namespace kmint::pigisland::knabbel {
    void HuntPigState::start(kmint::pigisland::shark *actor) {
        if(_g.num_nodes() != 634)
            return;

        auto &node = find_closest_node_to(_g, actor->smelledPos);

        std::cout << node.node_id() << std::endl;

        Astar astar(_g, actor->node().node_id(), node.node_id());
        astar.search();

        _path = astar.construct_path();
        actor->smelledPos = vector2d(0,0);
        actor->canEat = true;
    }

    void HuntPigState::execute(kmint::pigisland::shark *actor, kmint::delta_time dt) {
        if (!_path.empty()) {
            actor->node(_g[_path.back()]);
            _path.pop_back();
        }

        if (actor->fatigue++ >= 100) {
            actor->transitionTo(new TravelHomeState(_g));
        }

        if (kmint::math::distance(actor->location(), actor->boat_->location()) <= 50.0f) {
            actor->transitionTo(new FleeBoatState(_g));
        }

        if (_path.empty()) {
            std::cout << "reached pig pos" << std::endl;
            actor->transitionTo(new WanderState(_g));
        }
    }
}