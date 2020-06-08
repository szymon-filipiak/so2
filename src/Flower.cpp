#include <utility>

#include <iostream>
#include <thread>
#include "Flower.h"

void Flower::operator()() {
    while(_is_alive){
        std::this_thread::sleep_for(_refresh_rate);
        pollen_mutex.lock();
        has_pollen.store(true);
        pollen_mutex.unlock();
        std::cout<<"Pollen refreshed!\n";
    }
}

bool Flower::collect_pollen() {
    std::lock_guard<std::mutex> guard(pollen_mutex);
    if(has_pollen.load())
    {

        std::cout << "Pollen collected.\n";
        has_pollen.store(false);
        return true;
    } else
    {
        return false;
    }
}

Flower::Flower(const Position& pos, std::chrono::seconds refresh_rate) : pos(pos), _refresh_rate(refresh_rate), has_pollen(true), _is_alive{true}
{

}

void Flower::kill() {
    _is_alive = false;

}

