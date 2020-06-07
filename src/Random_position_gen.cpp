//
// Created by shiro on 07.06.2020.
//

#include "Random_position_gen.h"

Random_position_gen::Random_position_gen(int max_width, int max_height):max_width{max_width},max_height{max_height}{
    srand (time(NULL));
}
Position Random_position_gen::get_random_position() {
    Position  r_pos;
    do {
        r_pos.x = rand() % max_width;
        r_pos.y = rand() % max_height;
    }while(positions_contain(r_pos));


}
Random_position_gen::positions_contain(Position test_pos){
    for(int i = 0; i<positions.size; i++){
        if(positions[i]==test_pos){
            return true;
        }
    }
    return false;
}