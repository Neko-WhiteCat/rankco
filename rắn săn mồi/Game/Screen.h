#ifndef SCREEN_H
#define SCREEN_H
// Bảo vệ tệp tiêu đề khỏi bị định nghĩa nhiều lần trong chương trình.

#include <SFML/Graphics.hpp>
// Bao gồm thư viện đồ họa SFML để xử lý các thành phần đồ họa như cửa sổ và vẽ hình.

class Screen
    // Định nghĩa lớp `Screen`, đây là lớp cơ sở cho các màn hình trong trò chơi.
{
public:
    virtual void handleInput(sf::RenderWindow& window) = 0;
    // Phương thức ảo thuần túy (pure virtual), xử lý đầu vào từ người dùng (ví dụ: bàn phím, chuột).
    // Cần được định nghĩa trong lớp con kế thừa.

    virtual void update(sf::Time delta) = 0;
    // Phương thức ảo thuần túy, cập nhật trạng thái của màn hình.
    // `delta` là thời gian trôi qua giữa các khung hình, dùng để điều chỉnh tốc độ cập nhật.

    virtual void render(sf::RenderWindow& window) = 0;
    // Phương thức ảo thuần túy, vẽ các thành phần đồ họa của màn hình lên cửa sổ.
    // Cần được định nghĩa trong lớp con kế thừa.

};

#endif
// Kết thúc bảo vệ tệp tiêu đề.
