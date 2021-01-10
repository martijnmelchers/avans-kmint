#include <kmint/pigisland/boat.hpp>
#include <kmint/pigisland/shark.hpp>

namespace kmint::pigisland {
    class Main {
    public:
        Main() = default;

        void start();

        static Main *getInstance();

    private:
        static Main *_instance;
        // play::stage stage_ = play::stage{{1024, 768}};

    };
}
