#include <iostream>
#include "src/Bee.h"
#include <thread>

int main(int argc, char** argv)
{
    Flower flower{{3,4}};

    Flower flower1{{3,4}};
    Hive hive{{0,0},2};
    Bee bee{flower, hive, {0,0}, std::chrono::seconds{1}};
    Bee bee1{flower, hive, {0,0}, std::chrono::seconds{1}};
    Bee bee2{flower1, hive, {0,0}, std::chrono::seconds{1}};
    Bee bee3{flower1, hive, {0,0}, std::chrono::seconds{1}};


    std::thread flower_thread(std::ref(flower));
    std::thread flower_thread1(std::ref(flower1));
    std::thread bee_thread((bee));
    std::thread bee_thread1((bee1));
    std::thread bee_thread2((bee2));
    std::thread bee_thread3((bee3));
    bee_thread.join();
    bee_thread1.join();
    bee_thread2.join();
    bee_thread3.join();
    flower_thread.join();
	return 0;
}
