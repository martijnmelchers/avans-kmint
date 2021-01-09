#include <kmint/pigisland/boat.hpp>
#include "kmint/pigisland/state/state.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint::pigisland {
    class WanderState : public State<kmint::pigisland::boat> {

    private:
        std::vector<int> _path;
        map::map_graph& _g;
    public:
        explicit WanderState(map::map_graph& g);

        void start(kmint::pigisland::boat *actor) override;
        void execute(kmint::pigisland::boat *actor, kmint::delta_time dt) override;


    };
}