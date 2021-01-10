#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <kmint/pigisland/state/knabbel/wander_state.hpp>
#include <kmint/pigisland/pig.hpp>

namespace kmint::pigisland {
    shark::shark(map::map_graph &g, map::map_node &initial_node, play::stage &stage)
            : play::map_bound_actor{initial_node},
              stage(stage),
              drawable_{*this, graphics::image{shark_image()}} {
        this->transitionTo(new knabbel::WanderState(g));
    }

    void shark::act(delta_time dt) {
        t_passed_ += dt;
        if (to_seconds(t_passed_) >= 1 && node().node_info().kind != 'R') {
            _state->execute(this, dt);
            t_passed_ = from_seconds(0);
        } else if (to_seconds(t_passed_) >= 4 && node().node_info().kind == 'R') {
            _state->execute(this, dt);
            t_passed_ = from_seconds(0);
        }

        // laat ook even zien welke varkentjes hij ruikt
        for (auto i = begin_perceived(); i != end_perceived(); ++i) {
            auto const &a = *i;
            //std::cout << "Smelled a pig at " << a.location().x() << ", "
            //           << a.location().y() << "\n";
        }
    }

    void shark::transitionTo(State<shark> *state) {
        _state.reset(state);
        _state->start(this);
    }

    void shark::queuePigs() {
        stage.after_act.emplace_back([this] {
            auto locs = pigisland::random_pig_locations(100);
            for (auto loc : locs) {
                stage.build_actor<pigisland::pig>(loc);
            }
        });
    }

} // namespace kmint
