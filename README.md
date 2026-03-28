# Learning OpenGL Notes

這個 repository 用來記錄我跟著 LearnOpenGL 練習的學習過程。

## 專案目標

- 依章節實作 LearnOpenGL 範例
- 熟悉 OpenGL 核心概念（VAO / VBO / EBO、Shader、Texture）
- 保存每一階段可執行的練習結果

## 目前進度

- `00_Test`：環境與流程測試
- `01_HelloTriangle`：繪製第一個三角形
- `02_HelloTriangle (EBO ver.)`：使用 EBO 繪製矩形
- `03_ShaderUniform`：練習 `uniform` 變數
- `04_ShaderClass`：整理 Shader 載入與使用流程
- `05_Texture`：貼圖載入與混合（`container.jpg` + `awesomeface.png`）

## 使用技術

- C++
- OpenGL 3.3 Core
- GLFW
- GLAD
- stb_image
- Visual Studio（Windows）

## 專案結構（摘要）

- `includes/`：共用 header（如 GLM）
- `libs/`：第三方 library
- `glfw/`、`glm/`：以 vendor 方式放入專案

## 執行方式

1. 使用 Visual Studio 開啟 solution（例如根目錄 solution 檔）
2. 選擇想執行的章節專案（例如 `05_Texture`）
3. Build 並執行

## 備註

本專案以學習紀錄為主，內容會隨著練習進度持續更新。
