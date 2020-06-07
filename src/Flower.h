#ifndef SO2_PROJECT_FLOWER_H
#define SO2_PROJECT_FLOWER_H


#include <chrono>
#include <atomic>
#include <mutex>
#include "Position.h"

class Flower {
public:
    void operator() ();

    explicit Flower(Position pos, std::chrono::seconds refresh_rate = std::chrono::seconds(10));
    Position pos;
    bool collect_pollen();
    void kill();
    std::atomic<bool> has_pollen;
private:
    bool _is_alive;
    std::mutex pollen_mutex;
    std::chrono::seconds _refresh_rate{};
};


#endif //SO2_PROJECT_FLOWER_H
