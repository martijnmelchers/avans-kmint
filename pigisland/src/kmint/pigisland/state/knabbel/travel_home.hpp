#include <kmint/pigisland/shark.hpp>
#include "kmint/pigisland/state/state.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint::pigisland::knabbel {
    class TravelHomeState : public State<kmint::pigisland::shark> {

    private:
        std::vector<int> _path;
    public:
        explicit TravelHomeState(map::map_graph &g) : State<kmint::pigisland::shark>(g) {};
        void start(kmint::pigisland::shark *actor) override;
        void execute(kmint::pigisland::shark *actor, kmint::delta_time dt) override;
    };
}