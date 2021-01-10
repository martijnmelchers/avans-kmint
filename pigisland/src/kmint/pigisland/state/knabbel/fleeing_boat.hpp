#include <kmint/pigisland/shark.hpp>

namespace kmint::pigisland::knabbel {
    class FleeBoatState : public State<kmint::pigisland::shark> {

    private:
        std::vector<int> _path;
        int remainingFlees = 10;
    public:
        explicit FleeBoatState(map::map_graph &g) : State<kmint::pigisland::shark>(g) {};
        void start(kmint::pigisland::shark *actor) override;
        void execute(kmint::pigisland::shark *actor, kmint::delta_time dt) override;
    };
}