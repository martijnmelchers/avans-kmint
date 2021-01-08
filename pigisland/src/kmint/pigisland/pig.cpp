#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint::pigisland {


    pig::pig(math::vector2d location)
            : play::free_roaming_actor{location},
              drawable_{*this, pig_image()} {
    }


} // namespace kmint
