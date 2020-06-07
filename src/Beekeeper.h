#ifndef SO2_PROJECT_BEEKEEPER_H
#define SO2_PROJECT_BEEKEEPER_H
#include "Hive.h"
#include "Utils.h"

class Beekeeper {
public:
    void operator()(Hive& hive);

    explicit Beekeeper(int capacity, Position init_pos = {-1, 5},Destination init_dest = {HIVE});

    Position pos;
private:
    int capacity;
    bool is_alive;
    Position init_pos;
    Destination _dest;

    void move_to_dest(Hive &hive);
    void collect_honey(Hive &hive);
    void kill();

    bool in_hive(Hive &hive);
    bool in_home();
};


#endif //SO2_PROJECT_BEEKEEPER_H
