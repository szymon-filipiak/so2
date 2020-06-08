#ifndef SO2_PROJECT_BEE_H
#define SO2_PROJECT_BEE_H


#include "Flower.h"
#include "Hive.h"
#include "Utils.h"
#include <atomic>

class Bee {
public:
    Flower& flower;
    Hive& hive;
    Position pos;

    BeeState state;

    Bee(Flower& flower, Hive& hive, const Position& pos, std::chrono::seconds work_time);
    void operator()();
private:
    int id;

    std::chrono::seconds work_time;
    Destination _dest = UNKNOWN;

    bool _has_pollen;

    void move_to_dest();
    void update_destination();

    bool in_hive();
    bool in_flower();

    static int bees_count;
};


#endif //SO2_PROJECT_BEE_H
