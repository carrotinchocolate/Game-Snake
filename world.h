#pragma once

#include "window.h"
#include "world.h"
#include "apple.h"
#include "snake.h"


class World
{
    friend class Game;
public:
    World() = default;
    virtual ~World() = default;



    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    void HandleCollisions();
    sf::Vector2i FindRandomFreeCell() const;

    Snake snake_;
    Apple apple_;
    std::vector<Wall> walls_;
};