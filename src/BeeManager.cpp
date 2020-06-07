//
// Created by shiro on 07.06.20.
//

#include <thread>
#include "BeeManager.h"

void BeeManager::manager_loop() {

    for ( auto bee : bees) {
        switch  (bee.state)
        {
            case TRAVELING:
                break;
            case AT_FLOWER:
                //bee.collect_pollen();
                break;
            case AT_HIVE:
                if (bee.hive.is_free())
                {
                    bee.hive.enter_hive(1);
                    bee.state = IN_HIVE;

                }
                case IN_HIVE:
                    break;
                  //  std::thread makeHoney([]{

                    //});

        }
    }

}
