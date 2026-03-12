#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "視窗大小被更改成 " << height << " x " << width << std::endl;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// 頂點著色器
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//片段著色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource_2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	else
	{
		std::cout << "Successed!" << std::endl;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] =
	{
		0, 2, 3,
		0, 1, 2
	};

	//創建頂點數據
	unsigned int VBO;
	glGenBuffers(1, &VBO); // 新增一個 VBO，頂點數據
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//創建一個 VAO 對象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // 綁定 VAO 紀錄 glVertexAttribPointer 的屬性設定

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//創建頂點著色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//檢測 vertexShader 是否編譯成功
	int success_vertexShader;
	char infoLog_vertexShader[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertexShader);

	if (!success_vertexShader) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog_vertexShader);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_vertexShader << std::endl;
	}

	// Create fragmentShader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check the success of compiling fragment shader
	int success_fragmentShader;
	char infoLog_fragmentShader[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragmentShader);

	if (!success_fragmentShader) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_fragmentShader);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog_fragmentShader << std::endl;
	}

	//Create fragmentShader_2
	unsigned int fragmentShader_2;
	fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);

	//Check the success of compiling fragment shader
	int success_fragmentShader_2;
	char infoLog_fragmentShader_2[512];
	glGetShaderiv(fragmentShader_2, GL_COMPILE_STATUS, &success_fragmentShader_2);

	if (!success_fragmentShader_2) {
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLog_fragmentShader_2);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog_fragmentShader_2 << std::endl;
	}

	//Link two Shader to a Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check the success of linking shaders
	int success_shaderProgram;
	char infoLog_shaderProgram[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_shaderProgram);

	if (!success_shaderProgram) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_shaderProgram);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog_shaderProgram << std::endl;
	}

	//另一個shaderProgram;
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader_2);
	glLinkProgram(shaderProgram2);

	//Check the success of linking shaders
	int success_shaderProgram2;
	char infoLog_shaderProgram2[512];
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success_shaderProgram2);

	if (!success_shaderProgram2) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog_shaderProgram2);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog_shaderProgram2 << std::endl;
	}

	//Delete two shader object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader_2);


	//鏈接頂點屬性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProgram2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	glfwTerminate();
	return 0;
}