#pragma once
#include <SFML/Graphics.hpp>


class Snake
{
public:
    struct Segment
    {
        sf::Vector2i position;
        sf::RectangleShape shape;
        sf::Color color;
    };

    enum Direction
    {
        Up,
        Right,
        Down,
        Left,
        None
    };

public:
    Snake() = default;
    virtual ~Snake() = default;

    void Create(const sf::Vector2i& head_position);

    Direction GetDirection() const;
    void SetDirection(const Direction new_direction);
    sf::Vector2i GetHeadPosition() const;
    const std::vector<Segment>& GetBody() const;

    bool CheckSelfCollision() const;
    bool CheckWallCollision() const;
    void Update(const float dt);
    void Render(sf::RenderWindow& window);
    void Grow();
    void RestartAfterCollision();

    int GetScore() const;
    void IncreaseScore(const int delta_score);
    
    int GetLives() const;
    void DecreaseLivesByOne();

private:
    void MoveByOneCell();

    std::vector<Segment> body_;
    Direction direction_;
    int score_ = 0;
    int lives_ = 3;
  
};