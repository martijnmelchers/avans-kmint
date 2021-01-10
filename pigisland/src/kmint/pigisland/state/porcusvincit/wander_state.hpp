#include <kmint/pigisland/boat.hpp>
#include "kmint/pigisland/state/state.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint::pigisland::pv {
    class WanderState : public State<kmint::pigisland::boat> {

    private:
        std::vector<int> _path;
    public:
        explicit WanderState(map::map_graph &g) : State<kmint::pigisland::boat>(g) {};
        void start(kmint::pigisland::boat *actor) override;
        void execute(kmint::pigisland::boat *actor, kmint::delta_time dt) override;
        static char calculateBestDock(kmint::pigisland::boat *actor);
    };
}