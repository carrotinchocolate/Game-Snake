#include "apple.h"

extern const int BLOCK_SIZE;


void Apple::Create(const sf::Vector2i& new_position)
{
    position_ = new_position;
    shape_.setRadius(BLOCK_SIZE / 2);
}

sf::Vector2i Apple::GetPosition() const
{
    return position_;
}

void Update(const float dt)
{
    //здесь ничего не нужно
}

void Render(sf::RenderWindow& window)
{
    //отрисовываем shape_ в зависимости от position_
    shape_.setPosition({ (float)position_.x * BLOCK_SIZE, (float)position_.y * BLOCK_SIZE });
    //отрисовываем красным цветом
    shape_.setFillColor(sf::Color::Red);
    window.draw(shape_);
}