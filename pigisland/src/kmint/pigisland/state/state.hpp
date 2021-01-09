#pragma once

#include "kmint/play/actor.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace kmint::pigisland {
        template<class T>
        class State {
            static_assert(std::is_base_of<kmint::play::map_bound_actor, T>::value,
                          "T must inherit from map_bound_actor");

            // Something like:

        public:
            virtual void start(T *actor) = 0;

            virtual void execute(T *actor, kmint::delta_time dt) = 0;
        };
    }