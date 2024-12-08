#include <SFML/Graphics.hpp>
// Thư viện SFML hỗ trợ xử lý đồ họa.

#include <random>
#include <memory>
// Bao gồm thư viện để sinh số ngẫu nhiên và quản lý con trỏ thông minh.

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
// Bao gồm các tệp tiêu đề cần thiết cho các lớp `GameScreen`, `GameOverScreen`, và `Game`.

using namespace sfSnake;
// Sử dụng namespace `sfSnake` để rút gọn việc gọi tên các thành phần.

GameScreen::GameScreen() : snake_()
// Hàm khởi tạo của lớp `GameScreen`, khởi tạo đối tượng `snake_`.
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
// Phương thức xử lý các sự kiện đầu vào trên màn hình chơi game.
{
	snake_.handleInput();
	// Gọi phương thức xử lý đầu vào của đối tượng `snake_`.
}

void GameScreen::update(sf::Time delta)
// Phương thức cập nhật trạng thái màn hình chơi game.
{
	if (fruit_.size() == 0)
		// Nếu không có quả nào trong danh sách `fruit_`, tạo mới một quả.
		generateFruit();

	snake_.update(delta);
	// Cập nhật trạng thái của con rắn theo khoảng thời gian `delta`.

	snake_.checkFruitCollisions(fruit_);
	// Kiểm tra va chạm giữa con rắn và các quả trong danh sách `fruit_`.

	if (snake_.hitSelf())
		// Nếu con rắn tự va vào chính nó, chuyển màn hình sang `GameOverScreen` với điểm số hiện tại.
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
// Phương thức vẽ các thành phần của màn hình chơi game.
{
	snake_.render(window);
	// Vẽ con rắn lên cửa sổ.

	for (auto fruit : fruit_)
		// Duyệt qua danh sách các quả trong `fruit_`.
		fruit.render(window);
	// Vẽ từng quả lên cửa sổ.
}

void GameScreen::generateFruit()
// Phương thức tạo mới một quả tại vị trí ngẫu nhiên.
{
	static std::default_random_engine engine;
	// Tạo một đối tượng sinh số ngẫu nhiên.

	engine.seed(time(NULL));
	// Đặt seed cho bộ sinh số ngẫu nhiên bằng thời gian hiện tại.

	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);
	// Phân phối đều các giá trị ngẫu nhiên cho tọa độ `x` và `y` trong kích thước của màn hình,
	// đảm bảo tọa độ không vượt quá kích thước cửa sổ trừ đi kích thước của một node rắn.

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
	// Thêm một đối tượng `Fruit` mới vào danh sách `fruit_` với vị trí ngẫu nhiên.
}
