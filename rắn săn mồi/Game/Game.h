#ifndef GAME_H
#define GAME_H
// Phần bảo vệ tệp tiêu đề: ngăn việc định nghĩa lại tệp tiêu đề `Game.h` trong quá trình biên dịch.

#include <SFML/Graphics.hpp>
// Thư viện SFML để hỗ trợ xử lý đồ họa.

#include <SFML/Audio.hpp>
// Thư viện SFML để hỗ trợ xử lý âm thanh.

#include <vector>
#include <memory>
// Thư viện C++ cho các kiểu dữ liệu vector (`std::vector`) và con trỏ thông minh (`std::shared_ptr`).

#include "Screen.h"
// Bao gồm tệp tiêu đề `Screen.h` để sử dụng lớp `Screen`.

namespace sfSnake
	// Khai báo namespace `sfSnake` để nhóm các thành phần của trò chơi và tránh xung đột tên.
{
	class Game
		// Khai báo lớp `Game`, lớp chính điều khiển toàn bộ trò chơi.
	{
	public:
		Game();
		// Hàm khởi tạo của lớp `Game`.

		void run();
		// Phương thức chính để chạy trò chơi, bắt đầu vòng lặp game.

		void handleInput();
		// Phương thức xử lý các sự kiện đầu vào từ người chơi.

		void update(sf::Time delta);
		// Phương thức cập nhật trạng thái trò chơi dựa trên thời gian đã trôi qua (`delta`).

		void render();
		// Phương thức vẽ các đối tượng trong trò chơi lên cửa sổ.

		static const int Width = 640;
		static const int Height = 480;
		// Hai hằng số tĩnh định nghĩa chiều rộng (`Width`) và chiều cao (`Height`) của cửa sổ trò chơi.

		static std::shared_ptr<Screen> Screen;
		// Con trỏ thông minh tĩnh `Screen` để quản lý màn hình hiện tại của trò chơi,
		// chẳng hạn màn hình menu hoặc màn hình chính.

	private:
		sf::RenderWindow window_;
		// Cửa sổ hiển thị của trò chơi.

		sf::Music bgMusic_;
		// Đối tượng nhạc nền của trò chơi.

		static const sf::Time TimePerFrame;
		// Hằng số tĩnh đại diện cho thời gian của mỗi khung hình (frame).
	};
}

#endif
// Kết thúc phần bảo vệ tệp tiêu đề.
