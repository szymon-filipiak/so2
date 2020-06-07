#ifndef SO2_PROJECT_BEEKEEPER_H
#define SO2_PROJECT_BEEKEEPER_H
#include "Hive.h"

class Beekeeper {

    void operator()(Hive& hive);

    explicit Beekeeper(int capacity, Position init_pos = {-1, 5});

    Position pos;
private:
    int capacity;
    bool is_alive;
};


#endif //SO2_PROJECT_BEEKEEPER_H
