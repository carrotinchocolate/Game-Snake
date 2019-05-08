#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
    Wall() = default;
    virtual ~Wall() = default;

    void Create(const sf::Vector2f& top_left, const sf::Vector2f& bottom_right);

    bool CheckCellInWall(const sf::Vector2F&cell) const;

    void Update(const float dt);
    void Render(sf::RenderWindow& window);
  private:
    sf::Vector2f top_left_;
    sf::Vector2f bottom_right_;

    sf::RectangleShape shape_;

};