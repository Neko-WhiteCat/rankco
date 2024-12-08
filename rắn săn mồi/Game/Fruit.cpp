#include <cstdlib>
#include "Fruit.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace sfSnake;

const float Fruit::Radius = 7.f; // Bán kính cố định của quả

// Hàm khởi tạo quả với vị trí và loại quả
Fruit::Fruit(sf::Vector2f position, FruitType type)
    : type_(type)
{
    shape_.setPosition(position);             // Thiết lập vị trí
    shape_.setRadius(Fruit::Radius);          // Thiết lập bán kính
    shape_.setFillColor(type == FruitType::Speed ? sf::Color::Blue : sf::Color::Red); // Màu xanh cho quả tốc độ, màu đỏ cho quả thường
}

// Vẽ quả lên màn hình
void Fruit::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}

// Lấy khung bao quanh quả
sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}

// Lấy loại quả
FruitType Fruit::getType() const
{
    return type_;
}

// Tạo vị trí ngẫu nhiên không trùng với thân rắn
sf::Vector2f Fruit::getRandomPosition(const std::vector<SnakeNode>& snakeNodes)
{
    sf::Vector2f position;
    bool positionIsValid;

    do
    {
        position.x = std::rand() % (Game::Width / static_cast<int>(Radius)) * Radius;
        position.y = std::rand() % (Game::Height / static_cast<int>(Radius)) * Radius;

        positionIsValid = true;
        for (const auto& node : snakeNodes)
        {
            if (node.getBounds().contains(position))
            {
                positionIsValid = false;
                break;
            }
        }
    } while (!positionIsValid);

    return position;
}

// Tạo quả ngẫu nhiên với loại quả có thể là thường hoặc tốc độ
Fruit Fruit::createRandomFruit(const std::vector<SnakeNode>& snakeNodes)
{
    FruitType type = (std::rand() % 50 == 0) ? FruitType::Speed : FruitType::Normal; // 50% cơ hội tạo quả tốc độ
    return Fruit(getRandomPosition(snakeNodes), type);
}
