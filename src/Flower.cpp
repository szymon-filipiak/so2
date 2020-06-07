#include <iostream>
#include <thread>
#include "Flower.h"

void Flower::operator()() {
    while(_is_alive){
        std::this_thread::sleep_for(_refresh_rate);
        pollen_mutex.lock();
        _has_pollen.test_and_set();
        pollen_mutex.unlock();
        std::cout<<"Pollen refreshed!\n";
    }
}

bool Flower::collect_pollen() {
    std::lock_guard<std::mutex> guard(pollen_mutex);
    if(_has_pollen.test_and_set())
    {

        std::cout << "Pollen collected.\n";
        _has_pollen.clear();
        return true;
    } else
    {
        _has_pollen.clear();
        return false;
    }
}

Flower::Flower(Position pos, std::chrono::seconds refresh_rate) : pos(pos), _refresh_rate(refresh_rate), _has_pollen(true)
{

}

void Flower::kill() {
    _is_alive = false;

}
