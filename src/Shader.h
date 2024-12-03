#pragma once

#include "../Dependencies/glad/glad.h"
#include "../Dependencies/glfw/glfw3.h"

#include "../Dependencies/glm/glm.hpp"


class Shader {
public:
	Shader(const char* vertPath = nullptr, const char* fragPath = nullptr);

	void use() const;

	void setVec3(unsigned int uniformLocation, glm::vec3& value) const;
	void setBool(unsigned int uniformLocation, bool value) const;
	void setMat4(unsigned int uniformLocation, glm::mat4& matrix) const;

	unsigned int ID;

	unsigned int modelLoc;
	unsigned int viewLoc;
	unsigned int projectionLoc;
	unsigned int colorLoc;
	unsigned int isColoredLoc;
};