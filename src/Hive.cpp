#include <iostream>
#include "Hive.h"

bool Hive::enter_hive(int bee_id) {
    if(is_free()){
        count_mutex.lock();
        bees_count++;
        count_mutex.unlock();
        std::cout << "Bee with id: " << bee_id << " in hive!\n";
        return true;
    }
    return false;
}

void Hive::exit_hive(int bee_id) {
    std::lock_guard<std::mutex> hon_guard(honey_mutex);
    count_mutex.lock();
    bees_count--;
    count_mutex.unlock();
    honey += 20;
    std::cout << "Bee with id: " << bee_id << " has exited the hive!\n";
    std::cout << "Honey balance is: " << honey <<"\n";
}

bool Hive::is_free() {
    std::lock_guard<std::mutex> count_guard(count_mutex);
    return capacity > bees_count;
}

Hive::Hive(const Position& pos, size_t capacity) : pos(std::move(pos)), capacity(capacity){

}

