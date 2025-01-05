#include "Shader.h"

#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertPath, const char* fragPath) {
	if (vertPath == nullptr)
		return;

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERRO AO LER ARQUIVOS\n";
	}
	const char* vert = vertexCode.c_str();
	const char* frag = fragmentCode.c_str();

	unsigned int vertShader;
	unsigned int fragShader;

	int compileStatus;
	char infoLog[512];

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vert, NULL);
	glCompileShader(vertShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &frag, NULL);
	glCompileShader(fragShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);

	// deleta os shaders
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	modelLoc = glGetUniformLocation(ID, "model");
	projectionLoc = glGetUniformLocation(ID, "projection");
	alphaLoc = glGetUniformLocation(ID, "alpha");
	debugModeLoc = glGetUniformLocation(ID, "debugMode");
	hitBoxColorLoc = glGetUniformLocation(ID, "hitBoxColor");
}
void Shader::use() const {
	glUseProgram(ID);
}