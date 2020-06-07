#ifndef SO2_PROJECT_BEEMANAGER_H
#define SO2_PROJECT_BEEMANAGER_H


#include "Bee.h"
#include <vector>

class BeeManager {

    std::vector<Bee> bees;

    void manager_loop();
};


#endif //SO2_PROJECT_BEEMANAGER_H
