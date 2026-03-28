#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <string>

//callback function for adjusting viewport when resize the glfw window's width and height
// 這個 callback function 的參數是 GLFW 規定好的。發生狀態改變的時候，GLFW 會傳入該 window 的 height, width
// 並且處理 callback function 裡面定義的動作。
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// 人手按得比電腦跑的速度還慢，所以可以用這個方法。
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// 與 windowSizeCallback 的區別在這裡專注在可以繪圖的像素區塊大小
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 三角形 vertex data ( 有兩個 Vertex Attributes )
	float vectices[] = {
		// 位置					顏色
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f
	};

	// 建立一個 Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//建立一個 VAO，用來記錄等一下對 VBO 的操作
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//綁定 VAO 後，開始綁定 VBO 並操作
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vectices), vectices, GL_STATIC_DRAW);

	// 建立 Shader
	Shader myShader("shader.vert", "shader.frag");


	//設定 Vertex Attribute (位置屬性)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//設定 Vertex Attribute (顏色屬性)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		myShader.useShader();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents(); // 檢查是否有觸發任何事件，呼叫 Callback
	}

	glfwTerminate();

	return 0;
}