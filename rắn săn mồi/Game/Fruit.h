#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "SnakeNode.h"

namespace sfSnake
{
    // Loại quả trong trò chơi
    enum class FruitType
    {
        Normal, // Quả thông thường
        Speed   // Quả tăng tốc
    };

    class Fruit
    {
    public:
        Fruit(sf::Vector2f position = sf::Vector2f(0, 0), FruitType type = FruitType::Normal);
        // Tạo quả ngẫu nhiên, có thể là quả thường hoặc quả tốc độ
        static Fruit createRandomFruit(const std::vector<SnakeNode>& snakeNodes);

        void render(sf::RenderWindow& window); // Vẽ quả
        sf::FloatRect getBounds() const;      // Lấy khung bao quanh quả
        FruitType getType() const;            // Lấy loại quả

    private:
        sf::CircleShape shape_; // Hình tròn biểu diễn quả
        FruitType type_;        // Loại quả
        static const float Radius; // Bán kính quả

        // Tạo vị trí ngẫu nhiên không trùng với thân rắn
        static sf::Vector2f getRandomPosition(const std::vector<SnakeNode>& snakeNodes);
    };
}

#endif
