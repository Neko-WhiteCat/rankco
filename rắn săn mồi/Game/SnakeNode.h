#ifndef SNAKE_NODE_H      // Kiểm tra xem file này đã được bao gồm chưa. Nếu chưa, tiếp tục biên dịch file này
#define SNAKE_NODE_H      // Định nghĩa macro SNAKE_NODE_H để tránh việc bao gồm lại file này trong các file khác

#include <SFML/Graphics.hpp>  // Bao gồm thư viện đồ họa SFML để sử dụng các đối tượng đồ họa như hình chữ nhật (RectangleShape)

// Định nghĩa không gian tên sfSnake
namespace sfSnake
{
	// Khai báo lớp SnakeNode, đại diện cho một phần của con rắn trong trò chơi
	class SnakeNode
	{
	public:
		// Constructor của lớp SnakeNode, nhận vào một đối tượng sf::Vector2f làm vị trí khởi tạo cho node
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

		// Hàm để thiết lập vị trí của node từ một đối tượng sf::Vector2f
		void setPosition(sf::Vector2f position);

		// Hàm để thiết lập vị trí của node từ hai tham số float x và y
		void setPosition(float x, float y);

		// Hàm để di chuyển node bằng cách cộng thêm xOffset và yOffset vào tọa độ hiện tại
		void move(float xOffset, float yOffset);

		// Hàm để vẽ node (hình chữ nhật) lên cửa sổ đồ họa
		void render(sf::RenderWindow& window);

		// Hàm để lấy vị trí hiện tại của node dưới dạng sf::Vector2f
		sf::Vector2f getPosition() const;

		// Hàm để lấy phạm vi toàn cầu (bounding box) của hình chữ nhật node dưới dạng sf::FloatRect
		sf::FloatRect getBounds() const;

		// Các hằng số tĩnh (static) dùng để xác định chiều rộng và chiều cao của node
		static const float Width;  // Chiều rộng cố định của node
		static const float Height; // Chiều cao cố định của node

	private:
		// Đối tượng hình chữ nhật (sf::RectangleShape) đại diện cho phần tử của con rắn
		sf::RectangleShape shape_;

		// Vị trí của node, lưu trữ dưới dạng sf::Vector2f
		sf::Vector2f position_;
	};
}

#endif  // Kết thúc định nghĩa macro SNAKE_NODE_H
