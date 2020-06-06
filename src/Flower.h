#ifndef SO2_PROJECT_FLOWER_H
#define SO2_PROJECT_FLOWER_H


#include <chrono>

class Flower {
public:
    void operator() ();

    void collect_pollen();
private:
    std::chrono::seconds _refresh_rate;
    bool _has_pollen;
};


#endif //SO2_PROJECT_FLOWER_H
