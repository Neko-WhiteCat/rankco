#include <SFML/Graphics.hpp>
// Thư viện SFML hỗ trợ xử lý đồ họa.

#include <iostream>
#include <memory>
// Thư viện C++ để sử dụng `std::cout` và con trỏ thông minh `std::shared_ptr`.

#include "Game.h"
// Bao gồm tệp tiêu đề `Game.h` để sử dụng các thuộc tính và phương thức liên quan đến trò chơi.

#include "GameScreen.h"
#include "GameOverScreen.h"
// Bao gồm các tệp tiêu đề `GameScreen.h` và `GameOverScreen.h` để sử dụng các lớp màn hình trong trò chơi.

using namespace sfSnake;
// Sử dụng namespace `sfSnake` để rút gọn tên gọi của các lớp và phương thức.

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
// Hàm khởi tạo của lớp `GameOverScreen` nhận tham số `score` (điểm số của người chơi) và gán cho thuộc tính `score_`.
{
    font_.loadFromFile("game_over.ttf");
    // Tải phông chữ từ tệp `game_over.ttf`.

    text_.setFont(font_);
    // Đặt phông chữ cho đối tượng văn bản (`text_`).

    text_.setString("Your score: " + std::to_string(score) + "!"
        "\n\nPress [SPACE] to retry"
        "\n\nPress [ESC] to quit");
    // Đặt chuỗi nội dung hiển thị, bao gồm điểm số của người chơi,
    // hướng dẫn nhấn phím SPACE để chơi lại hoặc ESC để thoát.

    text_.setFillColor(sf::Color::Red);
    // Đặt màu chữ là đỏ.

    sf::FloatRect textBounds = text_.getLocalBounds();
    // Lấy khung hình chữ nhật bao quanh văn bản.

    text_.setOrigin(textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2);
    // Đặt tâm của văn bản vào chính giữa (cân chỉnh để hiển thị giữa màn hình).

    text_.setPosition(Game::Width / 2, Game::Height / 2);
    // Đặt vị trí văn bản tại trung tâm của cửa sổ trò chơi.
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
// Phương thức xử lý các sự kiện đầu vào khi ở màn hình kết thúc trò chơi.
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        // Kiểm tra nếu người chơi nhấn phím SPACE.
        Game::Screen = std::make_shared<GameScreen>();
    // Đặt màn hình hiện tại (`Screen`) thành `GameScreen`, bắt đầu trò chơi mới.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        // Kiểm tra nếu người chơi nhấn phím ESC.
        window.close();
    // Đóng cửa sổ trò chơi.
}

void GameOverScreen::update(sf::Time delta)
// Phương thức cập nhật trạng thái của màn hình kết thúc (trong trường hợp này không làm gì).
{

}

void GameOverScreen::render(sf::RenderWindow& window)
// Phương thức vẽ màn hình kết thúc lên cửa sổ trò chơi.
{
    window.draw(text_);
    // Vẽ văn bản lên cửa sổ.
}
