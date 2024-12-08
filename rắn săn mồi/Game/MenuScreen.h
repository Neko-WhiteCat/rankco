#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
// Bảo vệ tệp tiêu đề khỏi bị định nghĩa nhiều lần trong chương trình.

#include <SFML/Graphics.hpp>
// Bao gồm thư viện đồ họa SFML để xử lý giao diện đồ họa.

#include "Screen.h"
// Bao gồm tệp tiêu đề `Screen.h` để kế thừa lớp `Screen`.

namespace sfSnake
	// Định nghĩa không gian tên `sfSnake` cho các lớp liên quan đến trò chơi Snake.
{
	class MenuScreen : public Screen
		// Lớp `MenuScreen` kế thừa từ lớp cơ sở `Screen` (đa hình nằm ở đây).
	{
	public:
		MenuScreen();
		// Hàm khởi tạo `MenuScreen`, dùng để thiết lập màn hình menu.

		void handleInput(sf::RenderWindow& window) override;
		// Phương thức xử lý đầu vào từ người chơi (ghi đè từ lớp cơ sở).

		void update(sf::Time delta) override;
		// Phương thức cập nhật trạng thái của màn hình menu (ghi đè từ lớp cơ sở).

		void render(sf::RenderWindow& window) override;
		// Phương thức vẽ các thành phần giao diện của màn hình menu (ghi đè từ lớp cơ sở).

	private:
		sf::Font font_;
		// Thuộc tính lưu trữ font chữ được sử dụng trong màn hình menu.

		sf::Text snakeText_;
		// Thuộc tính chứa tiêu đề "Snake!" hiển thị trên màn hình.

		sf::Text text_;
		// Thuộc tính chứa các hướng dẫn "Press [SPACE] to play" và "Press [ESC] to quit".
	};
}

#endif
// Kết thúc bảo vệ tệp tiêu đề.
