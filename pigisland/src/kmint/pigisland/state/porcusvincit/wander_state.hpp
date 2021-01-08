#include "kmint/pigisland/state/state.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint::pigisland {
    class WanderState : public State<kmint::pigisland::boat> {
    public:
        void start(kmint::pigisland::boat *actor) override;

        void execute(kmint::pigisland::boat *actor, kmint::delta_time dt) override;
    };
}