#include "world.h"


extern const sf::Vector2i WORLD_SIZES;


void World::Create()
{
  Wall left;
  left.Create({0,0}, {0, WORLD_SIEZS.y - 1});
  walls_.push_back(std::move(left));
 
  Wall right;
  right.Create{WORLD_SIZES.x - 1, 0}, {WORLD_SIZES.x - 1, WORLD_SIZES.y - 1});
  walls_.push_back(std::move(right));
    
  Wall down;
  down.Create({0, WORLD_SIZES.y - 1}, {WORLD_SIZES.x - 1, WORLD_SIZES.y - 1});
  walls_.push_back(down);

  Wall up;
  up.Create({0,0}, {WORLD_SIZES.x - 1, 0});
  walls_.push_back(std::move(up));

  snake_.Create(FindRandomFreeCell());
  apple_.Create(FindRandomFreeCell());
}

void World::Update(const float dt)
{
    snake_.Update(dt);
    apple_.Update(dt);

    for (Wall& wall : walls_)
    {
        wall.Update(dt);
    }

    HandleCollisions();
}

void World::Render(sf::RenderWindow& window)
{
    snake_.Render(window);
    apple_.Render(window);

    for (Wall& wall : walls_)
    {
        wall.Render(window);
    }
}

void World::HandleCollisions()
{

   /* if (snake_.CheckSelfCollision())
    {
      // game over
    }*/

    for (const Wall& wall : walls_)
    {
      if (wall.CheckCellInWall(snake_.GetPosition()))
      {
        snake_.DecreaseLivesByOne();
        snake_.RestartAfterCollision();
        break;
      }

    }

   /* if (snake_.GetLives() == 0)
    {
      //game over  
    }*/

    if (snake_.GetBody()[0].position == apple_.GetPosition())
    {
      snake_.Grow();
      apple_.Create(FindRandomFreeCell());
      snake_.IncreaseScore(10);



    }
}

sf::Vector2i World::FindRandomFreeCell() const
{
    while (true)
    {
        bool is_random_cell_collided = false;
        const sf::Vector2i random_cell_position(
            std::rand() % world_sizes_.x,
            std::rand() % world_sizes_.y
        );

        // Check possible collisions with walls
        for (const Wall& wall : walls_)
        {
            if (wall.CheckIsCellInWall(random_cell_position))
            {
                is_random_cell_collided = true;
                break;
            }
        }

        // Check possible collisions with snake
        if (!is_random_cell_collided)
        {
            const auto& snake_body = snake_.GetBody();
            for (const auto& snake_segment : snake_body)
            {
                if (snake_segment.position == random_cell_position)
                {
                    is_random_cell_collided = true;
                    break;
                }
            }
        }

        // Check possible collision with apple
        if (!is_random_cell_collided)
        {
            if (apple_.GetPosition() == random_cell_position)
            {
                is_random_cell_collided = true;
            }
        }

        if (!is_random_cell_collided)
        {
            return random_cell_position;
        }
    }
}


}