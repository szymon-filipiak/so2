#include <ctime>
#include <cstdlib>
#include <tuple>
#include "PositionGenerator.h"

PositionGenerator::PositionGenerator(int max_width, int max_height):max_width{max_width},max_height{max_height}{
    srand (std::time(NULL));
}
Position PositionGenerator::get_random_position() {

    std::tuple<int,int> pos{rand() % max_width, rand() % max_height};
    while (already_occured(pos))
    {
        pos = {rand() % max_width, rand() % max_height};
    }
    positions.push_back(pos);
    return Position{std::get<0>(pos), std::get<1>(pos)};
}

bool PositionGenerator::already_occured(std::tuple<int,int> test_pos) {
    for (auto pos : positions)
    {
        if (pos == test_pos)
            return true;
    }
    return false;


}
