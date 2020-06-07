
#ifndef SO2_PROJECT_HIVE_H
#define SO2_PROJECT_HIVE_H


#include "Position.h"
#include <mutex>

class Hive {
public:
    Position pos{};
    int capacity{};
    int bees_count{};

    Hive(Position pos, int capacity);
    bool is_free();

    bool enter_hive(int bee_id);
    void exit_hive(int bee_id);
    std::mutex honey_mutex;
    std::mutex count_mutex;
    int honey = 0;
};


#endif //SO2_PROJECT_HIVE_H
