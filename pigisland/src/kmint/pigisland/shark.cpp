#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <kmint/pigisland/state/knabbel/wander_state.hpp>
#include <kmint/pigisland/pig.hpp>
#include <kmint/pigisland/state/knabbel/travel_home.hpp>
#include <kmint/pigisland/state/knabbel/fleeing_boat.hpp>

namespace kmint::pigisland {

    shark::shark(map::map_graph &g, map::map_node &initial_node, play::stage &stage)
            : play::map_bound_actor{initial_node},
              stage(stage),
              drawable_{*this, graphics::image{shark_image()}},
              _g(g) {
        this->transitionTo(new knabbel::WanderState(g));
    }

    void shark::act(delta_time dt) {
        t_passed_ += dt;
        if (to_seconds(t_passed_) >= node()[0].weight()) {
            if (!dynamic_cast<kmint::pigisland::knabbel::TravelHomeState *>(_state.get()) &&
                !dynamic_cast<kmint::pigisland::knabbel::FleeBoatState *>(_state.get())) {
                if (fatigue++ >= 100) {
                    transitionTo(new kmint::pigisland::knabbel::TravelHomeState(_g));
                } else if (kmint::math::distance(location(), boat_->location()) <= 50.0f) {
                    transitionTo(new kmint::pigisland::knabbel::FleeBoatState(_g));
                }
            }

            _state->execute(this, dt);
            t_passed_ = from_seconds(0);
        }

        // laat ook even zien welke varkentjes hij ruikt

    }

    void shark::transitionTo(State<shark> *state) {
        _state.reset(state);
        _state->start(this);
    }

    void shark::queuePigs() {
        stage.after_act.emplace_back([this] {
            auto locs = pigisland::random_pig_locations(100);
            for (auto loc : locs) {
                auto &pig = stage.build_actor<pigisland::pig>(loc);
                pig.setBoat(*boat_);
                pig.setShark(*this);
            }
        });
    }

    void shark::eat(play::actor *a) {
        if (canEat) {
            eatenPigs++;
            a->remove();
        }
    }

} // namespace kmint
