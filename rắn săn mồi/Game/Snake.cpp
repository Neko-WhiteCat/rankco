#include <SFML/Graphics.hpp> // Thư viện đồ họa để vẽ các đối tượng 2D
#include <memory>            // Thư viện hỗ trợ con trỏ thông minh
#include <iostream>          // Thư viện hỗ trợ nhập xuất dòng lệnh
#include "Snake.h"           // Định nghĩa lớp Snake
#include "Game.h"            // Định nghĩa tham số và logic trò chơi
#include "Fruit.h"           // Định nghĩa các loại quả
#include "SnakeNode.h"       // Định nghĩa các đoạn thân rắn
#include "GameOverScreen.h"  // Định nghĩa màn hình khi trò chơi kết thúc

using namespace sfSnake; // Sử dụng namespace sfSnake để tổ chức mã và tránh xung đột tên

// Định nghĩa kích thước ban đầu của rắn
const int Snake::InitialSize = 5; // Rắn bắt đầu với 5 đoạn thân

// Hàm khởi tạo Snake
Snake::Snake()
    : direction_(Direction::Up),         // Hướng mặc định ban đầu là "lên"
    lastDirection_(Direction::Up),    // Hướng di chuyển trước đó cũng là "lên"
    hitSelf_(false),                  // Trạng thái mặc định: rắn chưa tự cắn vào mình
    speedBoostActive_(false),         // Trạng thái tăng tốc ban đầu là tắt
    speedBoostTimer_(sf::Time::Zero)  // Bộ đếm thời gian tăng tốc ban đầu là 0
{
    initNodes(); // Khởi tạo các đoạn thân ban đầu của rắn

    // Tải âm thanh khi ăn quả
    pickupBuffer_.loadFromFile("eat.mp3"); // Tải tệp âm thanh cho sự kiện ăn quả
    pickupSound_.setBuffer(pickupBuffer_); // Gán tệp âm thanh vào đối tượng phát âm thanh
    pickupSound_.setVolume(30);            // Thiết lập âm lượng vừa phải

    // Tải âm thanh khi rắn chết
    dieBuffer_.loadFromFile("die.wav"); // Tải tệp âm thanh cho sự kiện rắn chết
    dieSound_.setBuffer(dieBuffer_);    // Gán tệp âm thanh vào đối tượng phát âm thanh
    dieSound_.setVolume(50);            // Thiết lập âm lượng lớn hơn một chút
}

// Hàm khởi tạo các đoạn thân ban đầu của rắn
void Snake::initNodes()
{
    // Tạo các đoạn thân ở vị trí giữa màn hình
    for (int i = 0; i < Snake::InitialSize; ++i)
    {
        // Vị trí đoạn thân thứ i được tính từ giữa màn hình trở xuống
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2 - SnakeNode::Width / 2,                       // Căn giữa theo chiều ngang
            Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)))); // Dịch chuyển theo chiều dọc
    }
}

// Xử lý đầu vào từ bàn phím để điều khiển hướng di chuyển của rắn
void Snake::handleInput()
{
    // Ưu tiên phím nhấn gần nhất, và ngăn rắn quay ngược
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && lastDirection_ != Direction::Down)
        direction_ = Direction::Up; // Đổi hướng lên
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && lastDirection_ != Direction::Up)
        direction_ = Direction::Down; // Đổi hướng xuống
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && lastDirection_ != Direction::Right)
        direction_ = Direction::Left; // Đổi hướng trái
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && lastDirection_ != Direction::Left)
        direction_ = Direction::Right; // Đổi hướng phải
}

// Cập nhật trạng thái của rắn (được gọi mỗi khung hình)
void Snake::update(sf::Time delta)
{
    static sf::Time elapsedTime = sf::Time::Zero; // Biến giữ thời gian tích lũy giữa các lần cập nhật
    elapsedTime += delta; // Cộng dồn thời gian trôi qua kể từ lần cập nhật trước

    // Nếu trạng thái tăng tốc đang hoạt động, giảm thời gian tăng tốc
    if (speedBoostActive_)
    {
        speedBoostTimer_ -= delta; // Giảm bộ đếm thời gian tăng tốc
        if (speedBoostTimer_ <= sf::Time::Zero) // Khi hết thời gian tăng tốc
        {
            speedBoostActive_ = false; // Tắt trạng thái tăng tốc
        }
    }

    // Nếu thời gian tích lũy đủ lớn, cập nhật trạng thái rắn
    if (elapsedTime.asMilliseconds() > (speedBoostActive_ ? 0 : 40)) // Tốc độ: 0ms khi tăng tốc, 40ms mặc định
    {
        move();               // Di chuyển rắn
        checkEdgeCollisions(); // Kiểm tra va chạm với biên màn hình
        checkSelfCollisions(); // Kiểm tra rắn có tự cắn vào mình không
        elapsedTime = sf::Time::Zero; // Đặt lại thời gian tích lũy
    }

    handleInput(); // Xử lý đầu vào từ bàn phím
}

// Di chuyển rắn theo hướng hiện tại
void Snake::move()
{
    // Di chuyển các đoạn thân (từ cuối đến đầu)
    for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
    {
        nodes_[i].setPosition(nodes_.at(i - 1).getPosition()); // Đoạn sau di chuyển đến vị trí của đoạn trước
    }

    // Di chuyển đầu rắn dựa trên hướng hiện tại
    switch (direction_)
    {
    case Direction::Up:
        nodes_[0].move(0, -SnakeNode::Height); // Dịch lên trên
        break;
    case Direction::Down:
        nodes_[0].move(0, SnakeNode::Height); // Dịch xuống dưới
        break;
    case Direction::Left:
        nodes_[0].move(-SnakeNode::Width, 0); // Dịch sang trái
        break;
    case Direction::Right:
        nodes_[0].move(SnakeNode::Width, 0); // Dịch sang phải
        break;
    }

    lastDirection_ = direction_; // Lưu hướng cuối cùng để tránh đổi ngược hướng ngay lập tức
}

// Kiểm tra va chạm biên màn hình
void Snake::checkEdgeCollisions()
{
    SnakeNode& headNode = nodes_[0]; // Đầu rắn

    // Nếu đầu rắn ra khỏi biên, đưa nó về phía đối diện
    if (headNode.getPosition().x < 0)
        headNode.setPosition(Game::Width - SnakeNode::Width, headNode.getPosition().y);
    else if (headNode.getPosition().x >= Game::Width)
        headNode.setPosition(0, headNode.getPosition().y);

    if (headNode.getPosition().y < 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height - SnakeNode::Height);
    else if (headNode.getPosition().y >= Game::Height)
        headNode.setPosition(headNode.getPosition().x, 0);
}

// Kiểm tra va chạm với chính thân rắn
void Snake::checkSelfCollisions()
{
    SnakeNode& headNode = nodes_[0]; // Đầu rắn

    // So sánh đầu rắn với từng đoạn thân còn lại
    for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
    {
        if (headNode.getBounds().intersects(nodes_[i].getBounds())) // Nếu có va chạm
        {
            dieSound_.play(); // Phát âm thanh rắn chết
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds())); // Tạm dừng trò chơi
            hitSelf_ = true; // Đặt trạng thái tự cắn vào mình
        }
    }
}

// Kiểm tra va chạm với quả
void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
    auto toRemove = fruits.end(); // Dùng để lưu vị trí quả bị ăn

    // Duyệt qua danh sách quả và kiểm tra va chạm với đầu rắn
    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if (it->getBounds().intersects(nodes_[0].getBounds())) // Nếu đầu rắn chạm quả
        {
            toRemove = it; // Ghi nhận quả bị ăn
            break;
        }
    }

    if (toRemove != fruits.end()) // Nếu có quả bị ăn
    {
        pickupSound_.play(); // Phát âm thanh ăn quả

        if (toRemove->getType() == FruitType::Speed) // Nếu quả là loại tăng tốc
        {
            speedBoostActive_ = true;         // Kích hoạt trạng thái tăng tốc
            speedBoostTimer_ = sf::seconds(5); // Rắn tăng tốc trong 5 giây
        }
        else
        {
            grow(); // Nếu là quả thường, rắn sẽ dài thêm
        }

        fruits.erase(toRemove); // Xóa quả đã ăn
        fruits.push_back(Fruit::createRandomFruit(nodes_)); // Sinh quả mới tại vị trí hợp lệ
    }
}

// Tăng kích thước rắn
void Snake::grow()
{
    sf::Vector2f newNodePosition = nodes_.back().getPosition(); // Vị trí đoạn thân cuối

    // Tính toán vị trí đoạn thân mới dựa trên hướng hiện tại
    switch (direction_)
    {
    case Direction::Up:
        newNodePosition.y += SnakeNode::Height; // Thêm đoạn ở phía dưới
        break;
    case Direction::Down:
        newNodePosition.y -= SnakeNode::Height; // Thêm đoạn ở phía trên
        break;
    case Direction::Left:
        newNodePosition.x += SnakeNode::Width; // Thêm đoạn bên phải
        break;
    case Direction::Right:
        newNodePosition.x -= SnakeNode::Width; // Thêm đoạn bên trái
        break;
    }

    nodes_.push_back(SnakeNode(newNodePosition)); // Thêm đoạn thân mới vào cuối rắn
}

// Lấy kích thước hiện tại của rắn
unsigned Snake::getSize() const
{
    return nodes_.size(); // Trả về số lượng đoạn thân rắn
}

// Kiểm tra trạng thái rắn tự cắn vào mình
bool Snake::hitSelf() const
{
    return hitSelf_; // Trả về trạng thái va chạm của rắn
}

// Vẽ rắn lên cửa sổ
void Snake::render(sf::RenderWindow& window)
{
    for (auto& node : nodes_) // Lặp qua từng đoạn thân
        node.render(window); // Vẽ từng đoạn thân lên màn hình
}
