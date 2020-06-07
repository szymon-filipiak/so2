#ifndef SO2_PROJECT_UTILS_H
#define SO2_PROJECT_UTILS_H

enum BeeState {
    TRAVELING,
    AT_FLOWER,
    AT_HIVE,
    IN_HIVE
};
enum Destination {
    UNKNOWN,
    HIVE,
    FLOWER,
    HOME
};

constexpr int BLOCK_SIZE = 32;
constexpr int NUMBER_OF_BLOCKS = 30;
constexpr int WINDOW_WIDTH = BLOCK_SIZE * NUMBER_OF_BLOCKS;
constexpr int WINDOW_HEIGHT = BLOCK_SIZE * NUMBER_OF_BLOCKS;


#endif //SO2_PROJECT_UTILS_H
