#include "SnakeNode.h" // Bao gồm tệp tiêu đề SnakeNode.h để định nghĩa lớp SnakeNode
#include <SFML/Graphics.hpp> // Bao gồm thư viện đồ họa SFML, cần thiết để sử dụng các đối tượng như RectangleShape

using namespace sfSnake; // Sử dụng namespace sfSnake để tránh xung đột tên với các namespace khác

// Định nghĩa chiều rộng và chiều cao mặc định của mỗi đoạn rắn
const float SnakeNode::Width = 10.f; // Chiều rộng cố định của mỗi node trong thân rắn
const float SnakeNode::Height = 10.f; // Chiều cao cố định của mỗi node trong thân rắn

// Hàm khởi tạo SnakeNode
SnakeNode::SnakeNode(sf::Vector2f position) // Nhận tham số vị trí (position) dưới dạng vector hai chiều
    : position_(position) // Khởi tạo giá trị cho thuộc tính position_ bằng tham số truyền vào
{
    shape_.setPosition(position_); // Đặt vị trí ban đầu của hình chữ nhật node theo position_
    shape_.setFillColor(sf::Color::Green); // Thiết lập màu sắc cho node, ở đây là màu xanh lá cây
    shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height)); // Thiết lập kích thước node với chiều rộng và chiều cao đã định nghĩa
    shape_.setOutlineThickness(0.f); // Thiết lập độ dày viền bằng 0 để các node nối sát nhau mà không có khoảng trống
}

// Hàm thiết lập vị trí tuyệt đối cho node (sử dụng vector)
void SnakeNode::setPosition(sf::Vector2f position)
{
    position_ = position; // Cập nhật vị trí nội bộ của node với giá trị mới
    shape_.setPosition(position_); // Đồng thời cập nhật vị trí hiển thị của hình chữ nhật
}

// Hàm thiết lập vị trí tuyệt đối cho node (sử dụng tọa độ x và y riêng biệt)
void SnakeNode::setPosition(float x, float y)
{
    position_.x = x; // Gán giá trị x mới cho vị trí nội bộ
    position_.y = y; // Gán giá trị y mới cho vị trí nội bộ
    shape_.setPosition(position_); // Cập nhật vị trí hiển thị của hình chữ nhật với giá trị x, y mới
}

// Hàm di chuyển node dựa trên khoảng dịch chuyển (offset)
void SnakeNode::move(float xOffset, float yOffset)
{
    position_.x += xOffset; // Cộng thêm giá trị dịch chuyển x vào tọa độ x hiện tại
    position_.y += yOffset; // Cộng thêm giá trị dịch chuyển y vào tọa độ y hiện tại
    shape_.setPosition(position_); // Cập nhật vị trí hiển thị của hình chữ nhật theo vị trí mới
}

// Hàm lấy tọa độ hiện tại của node
sf::Vector2f SnakeNode::getPosition() const
{
    return position_; // Trả về vị trí hiện tại của node dưới dạng vector hai chiều
}

// Hàm lấy khung bao quanh của node (phục vụ kiểm tra va chạm)
sf::FloatRect SnakeNode::getBounds() const
{
    return shape_.getGlobalBounds(); // Trả về hình chữ nhật bao quanh toàn cục của node
}

// Hàm vẽ node lên cửa sổ đồ họa
void SnakeNode::render(sf::RenderWindow& window)
{
    window.draw(shape_); // Vẽ hình chữ nhật đại diện cho node lên cửa sổ đồ họa
}
