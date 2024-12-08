#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H
// Phần bảo vệ tệp tiêu đề: ngăn việc định nghĩa lại tệp tiêu đề `GameScreen.h` trong quá trình biên dịch.

#include <SFML/Graphics.hpp>
// Thư viện SFML hỗ trợ xử lý đồ họa.

#include "Screen.h"
// Bao gồm tệp tiêu đề `Screen.h` để sử dụng lớp cơ sở `Screen`.

#include "Snake.h"
// Bao gồm tệp tiêu đề `Snake.h` để sử dụng lớp `Snake`.

#include "Fruit.h"
// Bao gồm tệp tiêu đề `Fruit.h` để sử dụng lớp `Fruit`.

namespace sfSnake
	// Khai báo namespace `sfSnake` để nhóm các thành phần của trò chơi và tránh xung đột tên.
{
	class GameScreen : public Screen
		// Lớp `GameScreen` kế thừa từ lớp cơ sở `Screen`, đại diện cho màn hình chơi game.
		// Đây là một ví dụ về đa hình (polymorphism) vì các phương thức của lớp `Screen` được ghi đè.
	{
	public:
		GameScreen();
		// Hàm khởi tạo của lớp `GameScreen`, dùng để khởi tạo các thành phần trên màn hình chơi game.

		void handleInput(sf::RenderWindow& window) override;
		// Phương thức xử lý đầu vào từ người chơi, ghi đè từ lớp `Screen`.

		void update(sf::Time delta) override;
		// Phương thức cập nhật trạng thái trò chơi, ghi đè từ lớp `Screen`.

		void render(sf::RenderWindow& window) override;
		// Phương thức vẽ các thành phần trên màn hình, ghi đè từ lớp `Screen`.

		void generateFruit();
		// Phương thức tạo mới một quả (fruit) tại vị trí ngẫu nhiên.

	private:
		Snake snake_;
		// Thuộc tính `snake_` đại diện cho con rắn trong trò chơi.

		std::vector<Fruit> fruit_;
		// Thuộc tính `fruit_` lưu trữ danh sách các quả (fruit) trên màn hình.
	};
}

#endif
// Kết thúc phần bảo vệ tệp tiêu đề.
