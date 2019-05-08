#include "game.h"

extern const sf::Vector2u WINDOW_SIZES(800, 600);
extern const sf::Vector2i WORLD_SIZES(40, 25);
extern const float BLOCK_SIZE = 18.0f; //только для отрисовки

Game::Game()
    : main_window_("Snake", WINDOW_SIZES)
{
    std::srand(static_cast<unsighed int>(stdP::time(nullptr)));
    message_box_({0, (int)WORLD_SIZES.y * BLOCK_SIZE}, {(int)WORLD_SIZES.x * BLOCK_SIZE, (int)WINDOW_SIZES.y - WORLD_SIZES.y * BLOCK_SIZE}, 100)
    world_.Create();
    
}


void Game::Run()
{
    const float updatets_per_seconds = 60.0f;
    const sf::Time time_per_update = sf::seconds(1.0f / updatets_per_seconds);

    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;

    while (!main_window_.CheckIsDone())
    {
        time_since_last_update += clock.restart();

        while (time_since_last_update >= time_per_update)
        {
            HandleInput();
            Update(time_per_update.asSeconds());
            time_since_last_update -= time_per_update;
        }
        NewMessage();
        Render();
        
    }
    if (world_.snake_.GetLives() == 0) && (world_.snake_.CheckSelfCollisions)
    {
      const std::string score_ = std::to_string(world_.snake_.GetScore());
      message_box_.Add("Game over. Your score = " + score_);

      exit(0);
    }
}


void Game::HandleInput()
{


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        world_.snake_.GetDirection() != Snake::Direction::Down)
    {
        world_.snake_.SetDirection(Snake::Direction::Up);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        world_.snake_.GetDirection() != Snake::Direction::Left)
    {
        world_.snake_.SetDirection(Snake::Direction::Right);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        world_.snake_.GetDirection() != Snake::Direction::Up)
    {
        world_.snake_.SetDirection(Snake::Direction::Down);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        world_.snake_.GetDirection() != Snake::Direction::Right)
    {
        world_.snake_.SetDirection(Snake::Direction::Left);
    }

    //particles_.Push(increment);
}

void Game::NewMessage()
{
  const std::string lives_ = std::to_string(world_.snake_.GetLives());
  message_box_.Headline("lives = " +  snake_lives + " score = " + snake_score);
  
}

void Game::Update(const float dt)
{
    main_window_.Update(dt);
    world_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();
    main_window_.Draw(world_);
    main_window_.EndDraw();
}