#include "snake.h"
#include <cassert>



//virtual ~Snake() = default
extern const int WINDOW_SIZES;
extern const int BLOCK_SIZE;

void Snake::Create(const sf::Vector2i& head_position)
{
    Segment head = {head_position, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)), sf::Color::Yellow};

    body_.push_back(std::move(head));
}

bool Snake::CheckSelfCollision() const
{
// цикл по body_, проверка на равенство координат с head_
  for (size_t i = 2, i <= body_.size(), i++)
  {
    if (body_[i].position == head_.position)
    {
      return 1;
    }
  }
    return 0;
  }
}

/*bool Snake::CheckWallCollision() const
{
  if (head_.x == WORLD_SIZES.x) or (head_.y == WORLD_SIZES.y)
  {
    return true
  }
  return false
}*/

void Snake::RestartAfterCollision()
{
    body_.clear();
    Create(sf::Vector2i(WORLD_SIZES.x / 2, WORLD_SIZES.y / 2));
}

sf::Vector2i Snake::GetHeadPosition() const
{
    assert(!body_.empty());
    return body_[0].position;
}

const std::vector<Segment>& Snake::GetBody() const
{
    return body_;
}

void Snake::Update(const float dt)
{
    MoveByOneCell();
}

void Snake::Render(sf::RenderWindow& window)
{
    //цикл по body_
    //отрисовка всех сегментов из body_
    for (Segment& segment : body_)
    {
      
        segment.shape.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        segment.shape.setPosition(sf::Vector2f(BLOCK_SIZE * segment.position.x, BLOCK_SIZE * segment.position.y));
        segment.shape.setFillColor(segment.color);
        window.draw(segment.shape);
    }
}


void Snake::MoveByOneCell()
{
      for (int i = body_.size() - 1; i > 0; i--)
    {
        body_[i].position = body_[i - 1].position;
    }
    if (direction_ == Right)
    {
      body_[0].x += 1
    }
    if (direction_ == Left)
    {
      body_[0].x -= 1
    }
    if (direction_ == Up)
    {
      body_[0].y -= 1
    }
    if (direction_ == Down)
    {
      body_[0].x += 1
    }
    const sf::Vector2f new_position((float)body_[0].position.x, (float)body_[0].position.y);
    body_[0].shape.setPosition(new_position);
}

void Snake::Grow()
{
    assert(!body_.empty());
    // первый случай: длина змеи равна 1 (т. е. есть только голова): добавление нового сегмента
    if (body_.size() == 1)
    {
        sf::Vector2i new_position;
        if (direction_ == Right)
        {
            new_position = body_[0].position + sf::Vector2i(-1, 0);
        }
        if (direction_ == Left)
        {
            new_position = body_[0].position + sf::Vector2i(1, 0);
        }
        if (direction_ == Up)
        {
            new_position = body_[0].position + sf::Vector2i(0, 1);
        }
        if (direction_ == Right)
        {
            new_position = body_[0].position + sf::Vector2i(0, -1);
    
        }
        Segment new_segment = {new_position, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)), sf::Color::Green};
        new_segment.shape.setPosition((float)new_segment.position.x, (float)new_segment.position.y);
        new_segment.shape.setFillColor(new_segment.color);

        body_.push_back(std::move(new_segment));   
    }
    // второй случай: длина змеи >= 2. тогда увеличить длину на основании двух последних сегментов  
    if (body_.size(0) >= 2)
    {
        sf::Vector2i new_position = body_.back().position;
        Segment new_segment = {new_position, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)), sf::Color::Green};
        new_segment.shape.setPosition((float)new_segment.position.x, (float)new_segment.position.y);
        new_segment.shape.setFillColor(new_segment.color);

        body_.push_back(std::move(new_segment));
    }
}


int Snake::GetScore() const
{
  return score_
}

void Snake::IncreaseScore(const int delta_score)
{
  score_ += delta_score
}

int Snake::GetLives() const
{
  return lives_
}

void Snake::DecreaseLivesByOne()
{
  lives_ -= 1
}