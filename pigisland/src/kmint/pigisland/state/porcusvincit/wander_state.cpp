#include <kmint/pigisland/state/state.hpp>
#include <kmint/pigisland/boat.hpp>
#include <kmint/astar/astar.hpp>
#include <numeric>
#include "wander_state.hpp"
#include "kmint/random.hpp"
#include "grain_dock.hpp"
#include "grass_dock.hpp"
#include "tree_dock.hpp"
#include <bits/stdc++.h>

namespace kmint::pigisland::pv {
    void WanderState::start(kmint::pigisland::boat *actor) {

    }

    void WanderState::execute(boat *actor, kmint::delta_time dt) {
        if (_path.empty()) {
            int next_index = random_int(0, _g.num_nodes());

            while (_g[next_index].node_info().kind != 'W' && _g[next_index].node_info().kind != 'R') {
                next_index = random_int(0, actor->node().num_edges());
            }

            kmint::graph::basic_node<map::map_node_info> &rNode = _g[next_index];

            Astar astar(_g, actor->node().node_id(), rNode.node_id());
            astar.search();

            play::image_drawable& image = (kmint::play::image_drawable& ) actor->drawable();
            image.set_tint(graphics::color(0,100,0));

            _path = astar.construct_path();
            astar.draw_path(_path);
        }

        actor->node(_g[_path.back()]);
        _path.pop_back();

        // Paint fully damaged, repair time!
        if (actor->paintDamage++ == 100) {
            char sugDock = calculateBestDock(actor);
            std::cout << "The boat is broken, going to dock: " << sugDock << std::endl;
            switch (sugDock) {
                case '1':
                    actor->transitionTo(new GrainDockState(_g));
                    break;
                case '2':
                    actor->transitionTo(new GrassDockState(_g));
                    break;
                case '3':
                    actor->transitionTo(new TreeDockState(_g));
                    break;
            };
        }

    }

    bool cmp(std::pair<char, float>& a,
             std::pair<char, float>& b)
    {
        return a.second < b.second;
    }

    char WanderState::calculateBestDock(kmint::pigisland::boat *actor) {
        // Default best dock is the grain dock
        float highest = 0;
        std::vector<std::pair<char, float>> chances;

        for (auto &x : actor->repairValues) {
            if(x.second.empty())
                return x.first;

            float average = std::accumulate(x.second.begin(), x.second.end(), decltype(x.second)::value_type(0)) / x.second.size();

            if(average > highest)
                highest = average;
        }

        for (auto &x : actor->repairValues) {
            float average = std::accumulate(x.second.begin(), x.second.end(), decltype(x.second)::value_type(0)) / x.second.size();

            chances.emplace_back(x.first, average / highest * 100);
        }

        std::sort(chances.begin(), chances.end(), cmp);

        for(auto &x : chances) {
            if(random_int(1, 100) - x.second < 0)
                return x.first;
        }

        // Anything goes wrong, default to 1
        return 1;
    }


}