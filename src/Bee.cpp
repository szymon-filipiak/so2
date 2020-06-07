#include <thread>
#include "Bee.h"

void Bee::operator()()//bool is_alive) {
{
    bool is_alive = true;
    while(is_alive) {
        if (_dest == FLOWER && in_flower()) {
            if(flower.collect_pollen())
            {
                _has_pollen = true;
                update_destination();
            }

        } else if (_dest == HIVE && in_hive()) {
            bool entered = false;
            while(!entered)
            {
                entered = hive.enter_hive(id);
            }
            std::this_thread::sleep_for(work_time);
            hive.exit_hive(id);
            _has_pollen = false;
            update_destination();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds{500});
            move_to_dest();
            update_destination();
        }
    }
}

void Bee::update_destination() {
    if(_has_pollen)
        _dest = HIVE;
    else
        _dest = FLOWER;
}

bool Bee::in_hive() {
    return pos == hive.pos;
}

bool Bee::in_flower() {
    return pos == flower.pos;
}

void Bee::move_to_dest() {
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

        case FLOWER:
        {

            if (flower.pos.x > pos.x)
                dx = 1;
            else if (flower.pos.x < pos.x)
                dx = -1;
            else
                dx = 0;


            if (flower.pos.y > pos.y)
                dy = 1;
            else if (flower.pos.y < pos.y)
                dy = -1;
            else
                dy = 0;
            break;
        }
        case UNKNOWN:break;
        case HOME:break;
    }

    pos.y += dy;
    pos.x += dx;

}

int Bee::bees_count = 0;

Bee::Bee(Flower &flower, Hive &hive, Position pos, std::chrono::seconds work_time) :
    flower(flower),
    hive(hive),
    pos(pos),
    work_time(work_time),
    _has_pollen(false)
{
    id = bees_count;
    bees_count++;
}

