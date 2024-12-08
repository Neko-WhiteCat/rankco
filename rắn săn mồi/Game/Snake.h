#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>  // Thư viện đồ họa SFML
#include <SFML/Audio.hpp>     // Thư viện âm thanh SFML
#include <vector>             // Thư viện vector của C++

#include "SnakeNode.h"        // Định nghĩa các nút của con rắn
#include "Fruit.h"            // Định nghĩa quả trong trò chơi

namespace sfSnake
{
    // Các hướng di chuyển của rắn
    enum class Direction
    {
        Left, Right, Up, Down
    };

    class Snake
    {
    public:
        Snake(); // Hàm khởi tạo

        void handleInput();   // Xử lý đầu vào từ bàn phím
        void update(sf::Time delta); // Cập nhật trạng thái của rắn
        void render(sf::RenderWindow& window); // Vẽ rắn lên màn hình

        void checkFruitCollisions(std::vector<Fruit>& fruits); // Kiểm tra va chạm với quả
        bool hitSelf() const; // Kiểm tra rắn có tự cắn không
        unsigned getSize() const; // Trả về kích thước hiện tại của rắn

    private:
        void move();               // Di chuyển rắn
        void grow();               // Tăng kích thước rắn khi ăn quả
        void activateMaxSpeed();   // Kích hoạt trạng thái tốc độ tối đa
        void checkEdgeCollisions();// Kiểm tra va chạm với cạnh màn hình
        void checkSelfCollisions();// Kiểm tra va chạm với chính mình
        void initNodes();          // Khởi tạo các đoạn thân rắn

        bool hitSelf_;             // Trạng thái va chạm với chính mình
        bool speedBoostActive_;    // Trạng thái tốc độ tối đa (quả tốc độ)
        sf::Time speedBoostTimer_; // Thời gian còn lại của trạng thái tốc độ tối đa

        sf::Vector2f position_;    // Vị trí đầu của rắn
        Direction direction_;      // Hướng hiện tại của rắn
        Direction lastDirection_;  // Hướng trước đó của rắn (ngăn đổi hướng ngược ngay lập tức)

        sf::SoundBuffer pickupBuffer_; // Âm thanh khi ăn quả
        sf::Sound pickupSound_;        // Đối tượng phát âm thanh khi ăn quả
        sf::SoundBuffer dieBuffer_;    // Âm thanh khi rắn chết
        sf::Sound dieSound_;           // Đối tượng phát âm thanh khi chết

        std::vector<SnakeNode> nodes_; // Các đoạn thân của rắn

        static const int InitialSize;  // Kích thước ban đầu của rắn
    };
}

#endif
