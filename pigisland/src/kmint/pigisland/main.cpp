#include <kmint/astar/astar.hpp>
#include <kmint/main.hpp>
#include "kmint/math/intersection.hpp"
#include "main.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/ui.hpp"

using namespace kmint;


int main() {
    auto main = kmint::pigisland::Main::getInstance();
    main->start();
}

namespace kmint::pigisland {
    void Main::start() {
        // een app object is nodig om
        ui::app app{};

        //  maak een venster aan
        ui::window window{app.create_window({1024, 768}, "pigisland", 1.0)};

        // maak een podium aan
      //   stage_ = play::stage{{1024, 768}};
        play::stage s{{1024, 768}};

        auto map = pigisland::map();
        auto &graph = map.graph();


        s.build_actor<play::background>(math::size(1024, 768),
                                             graphics::image{map.background_image()});
        s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());

        auto& boat = s.build_actor<pigisland::boat>(graph,
                                            pigisland::find_node_of_kind(graph, '1'));
        auto& shark = s.build_actor<pigisland::shark>(graph,
                                             pigisland::find_node_of_kind(graph, 'K'), s);


        shark.setBoat(boat);


        auto locs = pigisland::random_pig_locations(100);
        for (auto loc : locs) {
            auto& pig = s.build_actor<pigisland::pig>(loc);
            pig.setBoat(boat);
            pig.setShark(shark);
        }


        // Maak een event_source aan (hieruit kun je alle events halen, zoals
        // toetsaanslagen)
        ui::events::event_source event_source{};

        // main_loop stuurt alle actors aan.
        main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
            // gebruik dt om te kijken hoeveel tijd versterken is
            // sinds de vorige keer dat deze lambda werd aangeroepen
            // loop controls is een object met eigenschappen die je kunt gebruiken om de
            // main-loop aan te sturen.

            for (ui::events::event &e : event_source) {
                // event heeft een methode handle_quit die controleert
                // of de gebruiker de applicatie wilt sluiten, en zo ja
                // de meegegeven functie (of lambda) aanroept om met het
                // bijbehorende quit_event
                //
                e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
                e.handle_key_up([&](auto ke) {
                    switch (ke.key) {
                        case ui::events::key::p:
                            ctl.pause = !ctl.pause;
                            break;
                        case ui::events::key::r:
                            ctl.render = !ctl.render;
                            break;
                        case ui::events::key::opening_bracket:
                            ctl.time_scale /= 2.0;
                            break;
                        case ui::events::key::closing_bracket:
                            ctl.time_scale *= 2.0;
                            break;
                        case ui::events::key::d:
                            ctl.debug_overlay = !ctl.debug_overlay;
                        default:
                            break;
                    }
                });
            }
        });
    }

    Main *Main::_instance = nullptr;

    Main *Main::getInstance() {
        if (_instance == nullptr)
            _instance = new Main();

        return _instance;
    }
}

