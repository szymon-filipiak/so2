#include <iostream>
#include "src/Bee.h"
#include "src/Beekeeper.h"
#include <thread>
#include "include/cxxopts.hpp"
#include "src/PositionGenerator.h"
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    // OPTIONS
    cxxopts::Options options("main_app", "Multithread, customizable animation of bees' lives");

    options.add_options()
            ("b,bees", "Number of bees", cxxopts::value<size_t>()->default_value("2"))
            ("f,flowers", "Number of flowers", cxxopts::value<size_t>()->default_value("5"))
            ("H,hives", "Number of hives", cxxopts::value<size_t>()->default_value("2"))
            ("k,beekeepers", "Number of beekeepers", cxxopts::value<size_t>()->default_value("1"))
            ("p,pollen", "Pollen refresh rate [s]", cxxopts::value<size_t>()->default_value("5"))
            ("c, capacity", "Hives capacity", cxxopts::value<size_t>()->default_value("3"))
            ("w, work", "Bee work duration", cxxopts::value<size_t>()->default_value("7"))
            ("h,help", "Print help")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // VARIABLES
    auto flowers_count = result["flowers"].as<size_t >();
    auto bees_count = result["bees"].as<size_t >();
    auto beekeepers_count = result["beekeepers"].as<size_t >();
    auto hives_count = result["hives"].as<size_t >();
    auto pollen_refresh = std::chrono::seconds{result["pollen"].as<size_t>()};
    auto hives_capacity = result["capacity"].as<size_t>();
    auto bee_work_duration = std::chrono::seconds{result["work"].as<size_t>()};

    PositionGenerator pos_gen{NUMBER_OF_BLOCKS, NUMBER_OF_BLOCKS};

    void *raw_flowers = operator new[](flowers_count * sizeof(Flower));
    auto *flowers = static_cast<Flower *>(raw_flowers);

    void *raw_bees = operator new[](bees_count * sizeof(Bee));
    auto *bees = static_cast<Bee *>(raw_bees);

    void *raw_beekeepers = operator new[](beekeepers_count * sizeof(Beekeeper));
    auto *beekeepers = static_cast<Beekeeper *>(raw_beekeepers);

    void *raw_hives = operator new[](hives_count * sizeof(Hive));
    auto *hives = static_cast<Hive *>(raw_hives);

    for(int i = 0; i < flowers_count; i++)
    {
        auto coords = pos_gen.get_random_position();
        new(&flowers[i]) Flower{ Position{coords.x, coords.y}, pollen_refresh};
    }

    for(int i = 0; i < hives_count; i++)
    {
        new(&hives[i]) Hive(pos_gen.get_random_position(), hives_capacity);
    }

    for(int i = 0; i < bees_count; i++)
    {
        new(&bees[i]) Bee{flowers[rand() % flowers_count], hives[rand() % hives_count], pos_gen.get_random_position(), bee_work_duration};
    }

    for(int i = 0; i < beekeepers_count; i++)
    {
        new(&beekeepers[i]) Beekeeper(200,{-3,5});
    }

    //THREADS INIT

    for (int i = 0; i < bees_count; i++)
    {
        std::thread bee_thread(std::ref(bees[i]));
        bee_thread.detach();
    }

    for (int i = 0; i < flowers_count; i++)
    {
        std::thread flower_thread(std::ref(flowers[i]));
        flower_thread.detach();
    }


    for (int i = 0; i < beekeepers_count; i++)
    {
        std::thread beekeeper_thread(std::ref(beekeepers[i]), std::ref(hives[rand() % hives_count]));
        beekeeper_thread.detach();
    }

    //for (auto& bee : bees)
    //Beekeeper beekeeper{200};


    //std::this_thread::sleep_for(std::chrono::seconds{6});
    //std::thread beekeeper_thread(std::ref(beekeeper), std::ref(hives[0]));


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Texture grass_texture;
        if (!grass_texture.loadFromFile("res/grass.png"))
        {
            std::cout<< "ERROR: Could not load grass_texture grass.png";
            break;
        }

        window.clear();

        sf::Sprite grass_sprite;
        grass_sprite.setTexture(grass_texture);

        for(int y = 0; y < NUMBER_OF_BLOCKS; y++)
            for(int i = 0; i < NUMBER_OF_BLOCKS; i++)
            {
                grass_sprite.setPosition(i * BLOCK_SIZE, y * BLOCK_SIZE);
                window.draw(grass_sprite);
            }


        sf::Texture bee_texture;
        if (!bee_texture.loadFromFile("res/bee.png"))
        {
            break;
        }

        sf::Sprite bee_sprite;
        bee_sprite.setTexture(bee_texture);
        for(int i = 0; i < bees_count; i++)
        {
            bee_sprite.setPosition(bees[i].pos.x * BLOCK_SIZE, bees[i].pos.y * BLOCK_SIZE);
            window.draw(bee_sprite);
        }

        sf::Texture flower_texture_full;
        if (!flower_texture_full.loadFromFile("res/Full_flower.png"))
        {
            break;
        }

        sf::Texture flower_texture_empty;
        if (!flower_texture_empty.loadFromFile("res/Empty_flower.png"))
        {
            break;
        }

        sf::Sprite flower_sprite;
        for(int i = 0; i < flowers_count; i++)
        {
            flower_sprite.setTexture(flowers[i].has_pollen.load() ? flower_texture_full : flower_texture_empty);
            flower_sprite.setPosition(flowers[i].pos.x * BLOCK_SIZE, flowers[i].pos.y * BLOCK_SIZE);
            window.draw(flower_sprite);
        }

        sf::Texture hive_texture;
        if (!hive_texture.loadFromFile("res/Full_hive.png"))
        {
            break;
        }

        sf::Sprite hive_sprite;
        hive_sprite.setTexture(hive_texture);
        hive_sprite.setColor(sf::Color::Black);
        for(int i = 0; i < hives_count; i++)
        {
            hive_sprite.setPosition(hives[i].pos.x * BLOCK_SIZE, hives[i].pos.y * BLOCK_SIZE);
            window.draw(hive_sprite);
        }


        sf::Texture beekeeper_texture;
        if (!beekeeper_texture.loadFromFile("res/beekeeper.png"))
        {
            break;
        }

        sf::Sprite beekeeper_sprite;
        beekeeper_sprite.setTexture(beekeeper_texture);
        for(int i = 0; i < beekeepers_count; i++)
        {
            beekeeper_sprite.setPosition(beekeepers[i].pos.x * BLOCK_SIZE, beekeepers[i].pos.y * BLOCK_SIZE);
            window.draw(beekeeper_sprite);
        }


        window.display();
    }

    /*
    for (int i = bees_count - 1; i >= 0; --i) {
        bees[i].~Bee();
    }
    operator delete[](raw_bees);
*/
    return 0;
}

