# Hướng dẫn cài đặt SDL2 bằng Microsoft Visual Studio 2022 và Hướng dẫn chơi game:
+) tải các file VC.zip ở các đường link:https://github.com/libsdl-org/SDL/releases, https://github.com/libsdl-org/SDL_image/releases, https://github.com/libsdl-org/SDL_mixer/releases, https://github.com/libsdl-org/SDL_ttf/releases.
+) giải nén và cho vào cùng 1 file tên vslib.
+) tải Microsoft Visual Studio 2022 ở : https://download.com.vn/download/visual-studio-105771#google_vignette
+) chọn Create a new project -> chọn empty project
+) Chọn Source Files ở thanh bên trái -> Add -> Existing Item
+) Chỉnh Debug x64 trên thanh công cụ
+) Chọn Project -> Properties :
- chọn Configuration Properties -> VC++ Directories -> Include Directories -> Edit, sau đó chọn file include của 4 file vừa tải;
- Configuration Properties -> Linker -> Additional Dependencies -> Edit, sau đó thêm SDL2.lib; SDL2main.lib; SDL2_image.lib, SDL2_mixer.lib, SDL2_ttf.lib
- chọn Configuration Properties -> VC++ Directories -> Library Directories -> Edit, sau đó chọn file x64 của file lib của 4 file.
- mở tìm kiếm trong window setting tìm Edit the system environment variables -> chọn Environment Variables -> chọn Path trong mục System variables
