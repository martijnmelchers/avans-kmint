#include <kmint/pigisland/state/porcusvincit/wander_state.hpp>
#include "kmint/pigisland/resources.hpp"

namespace kmint::pigisland {
    boat::boat(map::map_graph &g, map::map_node &initial_node)
            : play::map_bound_actor{initial_node},
              drawable_{*this, graphics::image{boat_image()}}, _g(g){
        this->transitionTo(new pv::WanderState(_g));

        repairValues['1'] = std::vector<int>();
        repairValues['2'] = std::vector<int>();
        repairValues['3'] = std::vector<int>();
    }


    void boat::act(delta_time dt) {
        t_passed_ += dt;
       // std::cout << node().node_info().kind << std::endl;
        if (to_seconds(t_passed_) >= 1 && node().node_info().kind != 'R') {
            _state->execute(this, dt);
            t_passed_ = from_seconds(0);
        } else if(to_seconds(t_passed_) >= 4 && node().node_info().kind == 'R') {
            _state->execute(this, dt);
            t_passed_ = from_seconds(0);
        }

    }

    boat::~boat() {
    }

    void boat::repair(char dock, int repairAmount) {
        paintDamage = paintDamage - repairAmount;
        repairValues[dock].push_back(repairAmount);
    }

    void boat::transitionTo(State<boat> *state) {
        _state.reset(state);
        _state->start(this);
    }

} // namespace kmint
