//
// Created by shiro on 07.06.2020.
//

#ifndef SO2_RANDOM_POSITION_GEN_H
#define SO2_RANDOM_POSITION_GEN_H

#include <vector>
#include "Position.h"

class PositionGenerator {
public:
    PositionGenerator(int max_height, int max_width);

    Position get_random_position();

private:
    std::vector<std::tuple<int,int>> positions;
    int max_height;
    int max_width;

    bool already_occured(std::tuple<int,int> test_pos);
};
#endif //SO2_RANDOM_POSITION_GEN_H
