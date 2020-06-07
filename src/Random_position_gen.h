//
// Created by shiro on 07.06.2020.
//

#ifndef SO2_RANDOM_POSITION_GEN_H
#define SO2_RANDOM_POSITION_GEN_H

#include <vector>

class Random_position_gen {
public:
    Random_position_gen(int max_height, int max_width);

private:
    std::vector<Position> positions;
    int max_height;
    int max_width;

    Position get_random_position();
    bool positions_contain(Position test_pos);
};
#endif //SO2_RANDOM_POSITION_GEN_H
