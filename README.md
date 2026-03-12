# LearnOpenGL

OpenGL 練習專案，使用 C++ 與 OpenGL 3.3 Core Profile。

## 外部函式庫

| 函式庫 | 用途 | 下載連結 |
|--------|------|----------|
| [GLFW 3](https://www.glfw.org/) | 視窗管理與 OpenGL Context 建立 | https://www.glfw.org/download.html |
| [GLAD](https://glad.dav1d.de/) | OpenGL Function Loader | https://glad.dav1d.de/ (選擇 OpenGL 3.3, Core Profile) |

## 環境設定

1. 下載 GLFW 與 GLAD。
2. 在 Visual Studio 專案屬性中設定：
   - **Include 路徑**：加入 GLFW 和 GLAD 的 `include` 資料夾
   - **Library 路徑**：加入 GLFW 的 `lib` 資料夾
   - **連結器 > 額外相依性**：加入 `glfw3.lib;opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib`
3. 將 `glad.c` 加入專案一起編譯。
