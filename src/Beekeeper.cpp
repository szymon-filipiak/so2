//
// Created by shiro on 07.06.20.
//

#include "Beekeeper.h"

void Beekeeper::operator()(Hive &hive) {
    while(is_alive)
    {

    }

}

Beekeeper::Beekeeper(int capacity, Position init_pos) : capacity{capacity}, pos{init_pos}, is_alive{true}{

}
