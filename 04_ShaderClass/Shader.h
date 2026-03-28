#ifndef  SHADER_H_
#define SHADER_H_

#include <glad/glad.h> //包含 glad 可以取得所有 OpenGL 必須的 header

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//Program ID
	unsigned int ID;

	// Construct shader
	Shader(const char* vertexPath, const char* fragmentPath);

	void useShader();
	// Uniform tools
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:


	void CompileShader(std::string& vShaderCode, std::string& fShaderCode);
	void CheckShaderCompile(unsigned int shader, std::string type);
	void CheckShaderLink();
};


#endif // ! SHADER_H_

