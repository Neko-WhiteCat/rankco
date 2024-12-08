#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H
// Phần bảo vệ tệp tiêu đề: ngăn việc định nghĩa lại tệp tiêu đề `GameOverScreen.h` trong quá trình biên dịch.

#include <SFML/Graphics.hpp>
// Thư viện SFML hỗ trợ xử lý đồ họa.

#include "Screen.h"
// Bao gồm tệp tiêu đề `Screen.h` để sử dụng lớp cơ sở `Screen`.

namespace sfSnake
	// Khai báo namespace `sfSnake` để nhóm các thành phần của trò chơi và tránh xung đột tên.
{
	class GameOverScreen : public Screen
		// Lớp `GameOverScreen` kế thừa từ lớp `Screen`, đại diện cho màn hình kết thúc trò chơi.
	{
	public:
		GameOverScreen(std::size_t score);
		// Hàm khởi tạo của lớp `GameOverScreen`, nhận tham số `score` để hiển thị điểm số người chơi đạt được.

		void handleInput(sf::RenderWindow& window) override;
		// Phương thức xử lý các sự kiện đầu vào, ghi đè từ lớp `Screen`.

		void update(sf::Time delta) override;
		// Phương thức cập nhật trạng thái màn hình, ghi đè từ lớp `Screen`.

		void render(sf::RenderWindow& window) override;
		// Phương thức vẽ các thành phần của màn hình kết thúc lên cửa sổ, ghi đè từ lớp `Screen`.

	private:
		sf::Font font_;
		// Thuộc tính `font_` dùng để lưu phông chữ hiển thị trên màn hình.

		sf::Text text_;
		// Thuộc tính `text_` dùng để hiển thị nội dung văn bản, bao gồm điểm số và hướng dẫn điều khiển.

		unsigned score_;
		// Thuộc tính `score_` lưu điểm số của người chơi để hiển thị.
	};
}

#endif
// Kết thúc phần bảo vệ tệp tiêu đề.
