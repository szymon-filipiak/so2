//
// Created by shiro on 07.06.20.
//

#include <thread>
#include <iostream>
#include "Beekeeper.h"

void Beekeeper::operator()(Hive &hive) {
    while(is_alive)
    {
        if(_dest == HIVE && in_hive(hive)){
            collect_honey(hive);
            _dest = HOME;
            std::this_thread::sleep_for(std::chrono::milliseconds{500});
        } else if(_dest == HOME && in_home()){
            //kill();
            std::this_thread::sleep_for(std::chrono::seconds{5});
            _dest = HIVE;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds{500});
            move_to_dest(hive);
        }
    }

}
void Beekeeper::move_to_dest(Hive &hive) {
    int dx = 0, dy = 0;
    switch (_dest)
    {
        case HIVE:
        {
            if (hive.pos.x > pos.x)
                dx = 1;
            else if (hive.pos.x < pos.x)
                dx = -1;
            else
                dx = 0;


            if (hive.pos.y > pos.y)
                dy = 1;
            else if (hive.pos.y < pos.y)
                dy = -1;
            else
                dy = 0;
            break;
        }
        case UNKNOWN:break;
        case HOME:
        {
            if (init_pos.x > pos.x)
                dx = 1;
            else if (init_pos.x < pos.x)
                dx = -1;
            else
                dx = 0;


            if (init_pos.y > pos.y)
                dy = 1;
            else if (init_pos.y < pos.y)
                dy = -1;
            else
                dy = 0;
            break;
        }
        case FLOWER:break;
    }

    pos.y += dy;
    pos.x += dx;

}
bool Beekeeper::in_hive(Hive &hive){
    return pos == hive.pos;
}
bool Beekeeper::in_home(){
    return pos == init_pos;
}
void Beekeeper::collect_honey(Hive &hive){
    std::lock_guard<std::mutex> guard(hive.honey_mutex);
    if(hive.honey>0){
        if(hive.honey>capacity){
            hive.honey-=capacity;
        }else{
            hive.honey = 0;
        }
        std::cout << "Beekeeper has exited the hive!\n";
        std::cout << "Honey balance is: " << hive.honey <<"\n";
    }else{
        std::cout << "Beekeeper has exited the hive without honey!\n";
        std::cout << "Honey balance is: " << hive.honey <<"\n";
    }
}
void Beekeeper::kill(){
    is_alive = false;
}


Beekeeper::Beekeeper(int capacity, Position init_pos, Destination init_dest) : capacity{capacity}, pos{init_pos}, init_pos{init_pos}, _dest{init_dest}, is_alive{true}{

}
