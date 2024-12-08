#include <SFML/Graphics.hpp>
// Bao gồm thư viện SFML để xử lý đồ họa.

#include <memory>
// Bao gồm thư viện hỗ trợ con trỏ thông minh.

#include "GameScreen.h"
// Bao gồm tệp tiêu đề `GameScreen.h` để chuyển sang màn hình chơi game.

#include "MenuScreen.h"
// Bao gồm tệp tiêu đề `MenuScreen.h` để định nghĩa các phương thức liên quan đến màn hình menu.

#include "Game.h"
// Bao gồm tệp tiêu đề `Game.h` để truy cập các thuộc tính và phương thức của lớp `Game`.

using namespace sfSnake;
// Sử dụng không gian tên `sfSnake` để giảm việc viết lặp tên không gian.

MenuScreen::MenuScreen()
// Hàm khởi tạo `MenuScreen`, dùng để khởi tạo màn hình menu.
{
	font_.loadFromFile("game_over.ttf");
	// Tải font từ tệp `game_over.ttf`.

	text_.setFont(font_);
	// Thiết lập font chữ cho đối tượng `text_`.

	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");
	// Gán chuỗi hiển thị hướng dẫn chơi lên `text_`.

	snakeText_.setFont(font_);
	// Thiết lập font chữ cho đối tượng `snakeText_`.

	snakeText_.setString("Snake! Rank co");
	// Gán chuỗi tiêu đề "Snake! Rank co" vào `snakeText_`.

	snakeText_.setFillColor(sf::Color::Green);
	// Đặt màu chữ của `snakeText_` thành màu xanh lá cây.

	snakeText_.setCharacterSize(32);
	// Đặt kích thước chữ của `snakeText_` là 32.

	snakeText_.setStyle(sf::Text::Bold);
	// Đặt kiểu chữ của `snakeText_` là đậm (bold).

	sf::FloatRect textBounds = text_.getLocalBounds();
	// Lấy giới hạn của `text_` để căn chỉnh vị trí.

	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	// Đặt điểm gốc của `text_` là trung tâm.

	text_.setPosition(Game::Width / 2, Game::Height / 2);
	// Đặt vị trí của `text_` ở giữa màn hình game.

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	// Lấy giới hạn của `snakeText_` để căn chỉnh vị trí.

	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	// Đặt điểm gốc của `snakeText_` là trung tâm.

	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
	// Đặt vị trí của `snakeText_` ở 1/4 chiều cao màn hình.
}

void MenuScreen::handleInput(sf::RenderWindow& window)
// Phương thức xử lý đầu vào từ người chơi trên màn hình menu.
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		// Nếu phím `SPACE` được nhấn:
		Game::Screen = std::make_shared<GameScreen>();
	// Chuyển sang màn hình chơi game (`GameScreen`).

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		// Nếu phím `ESC` được nhấn:
		window.close();
	// Đóng cửa sổ trò chơi.
}

void MenuScreen::update(sf::Time delta)
// Phương thức cập nhật trạng thái màn hình menu.
{
	static bool movingLeft = false;
	static bool movingRight = true;
	// Biến tĩnh để điều khiển chuyển động của `snakeText_`.

	if (movingRight)
		// Nếu `snakeText_` đang quay theo chiều kim đồng hồ:
	{
		snakeText_.rotate(delta.asSeconds());
		// Quay chữ theo chiều kim đồng hồ với tốc độ dựa trên thời gian.

		if (static_cast<int>(snakeText_.getRotation()) == 10)
			// Khi góc quay đạt đến 10 độ:
		{
			movingRight = false;
			movingLeft = true;
			// Đổi hướng quay thành ngược chiều kim đồng hồ.
		}
	}

	if (movingLeft)
		// Nếu `snakeText_` đang quay ngược chiều kim đồng hồ:
	{
		snakeText_.rotate(-delta.asSeconds());
		// Quay chữ ngược chiều kim đồng hồ.

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
			// Khi góc quay đạt đến 350 độ:
		{
			movingLeft = false;
			movingRight = true;
			// Đổi hướng quay thành theo chiều kim đồng hồ.
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
// Phương thức vẽ các thành phần lên màn hình.
{
	window.draw(text_);
	// Vẽ `text_` chứa các hướng dẫn.

	window.draw(snakeText_);
	// Vẽ `snakeText_` chứa tiêu đề trò chơi.
}
