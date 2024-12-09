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
	viewLoc = glGetUniformLocation(ID, "view");
	projectionLoc = glGetUniformLocation(ID, "projection");
	colorLoc = glGetUniformLocation(ID, "color");
	isColoredLoc = glGetUniformLocation(ID, "isColored");
}
void Shader::use() const {
	glUseProgram(ID);
}

void Shader::setMat4(unsigned int uniformLocation, glm::mat4& matrix) const {
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setVec3(unsigned int uniformLocation, glm::vec3& vector) const {
	glUniform3fv(uniformLocation, 1, &vector[0]);
}

void Shader::setBool(unsigned int uniformLocation, bool value) const {
	glUniform1i(uniformLocation, value);
}