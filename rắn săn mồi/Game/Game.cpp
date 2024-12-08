#include <SFML/Graphics.hpp> // Thư viện đồ họa SFML
#include <memory>            // Thư viện hỗ trợ con trỏ thông minh
#include "MenuScreen.h"      // Khai báo màn hình menu
#include "Game.h"            // Khai báo lớp Game

using namespace sfSnake; // Sử dụng namespace sfSnake để tránh xung đột tên

// Tăng tốc độ khung hình lên 60 FPS
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 144.f);
// Thời gian mỗi khung hình (frame), được tính toán để đạt tốc độ 60 FPS (1 giây chia cho 60)

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
// Khởi tạo màn hình chính của trò chơi, ban đầu là MenuScreen, sử dụng con trỏ thông minh để quản lý

// Hàm khởi tạo lớp Game
Game::Game()
    : window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
    // Tạo cửa sổ trò chơi với kích thước cố định (Width x Height) và tiêu đề là "sfSnake"
{
    bgMusic_.openFromFile("canon.mp3"); // Mở tệp nhạc nền
    bgMusic_.setLoop(true);             // Thiết lập chế độ lặp lại nhạc nền
    bgMusic_.play();                    // Bắt đầu phát nhạc nền
}

// Xử lý các sự kiện đầu vào từ bàn phím hoặc chuột
void Game::handleInput()
{
    sf::Event event; // Đối tượng để lưu trữ sự kiện
    while (window_.pollEvent(event)) // Kiểm tra và xử lý tất cả các sự kiện trong hàng đợi
    {
        if (event.type == sf::Event::Closed) // Nếu sự kiện là đóng cửa sổ
            window_.close();                 // Đóng cửa sổ trò chơi
    }

    Game::Screen->handleInput(window_);
    // Chuyển sự kiện đầu vào tới màn hình hiện tại để xử lý (ví dụ: menu hoặc gameplay)
}

// Cập nhật trạng thái trò chơi
void Game::update(sf::Time delta)
{
    Game::Screen->update(delta);
    // Cập nhật logic của màn hình hiện tại, truyền vào delta để tính toán dựa trên thời gian trôi qua
}

// Vẽ nội dung lên màn hình
void Game::render()
{
    window_.clear(); // Xóa nội dung cũ trên cửa sổ

    Game::Screen->render(window_); // Gọi phương thức render của màn hình hiện tại

    window_.display(); // Hiển thị nội dung mới lên màn hình
}

// Vòng lặp chính của trò chơi
void Game::run()
{
    sf::Clock clock; // Đồng hồ dùng để tính thời gian giữa các khung hình
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // Thời gian tích lũy từ lần cập nhật cuối

    while (window_.isOpen()) // Vòng lặp tiếp tục khi cửa sổ đang mở
    {
        sf::Time delta = clock.restart(); // Lấy thời gian từ lần đo trước đó và đặt lại đồng hồ
        timeSinceLastUpdate += delta; // Tích lũy thời gian trôi qua

        // Xử lý các khung hình bị lỡ để đảm bảo tốc độ game nhất quán
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame; // Trừ đi thời gian khung hình đã xử lý

            handleInput();           // Xử lý đầu vào
            update(TimePerFrame);    // Cập nhật logic game
        }

        render(); // Vẽ nội dung sau khi logic game đã được cập nhật đầy đủ
    }
}
