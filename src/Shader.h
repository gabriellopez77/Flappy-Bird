#pragma once

#include "../Dependencies/glm/glm.hpp"

class Shader {
public:
	Shader(const char* vertPath = nullptr, const char* fragPath = nullptr);

	void use() const;

	unsigned int ID;

	unsigned int modelLoc;
	unsigned int projectionLoc;
	unsigned int alphaLoc;
	unsigned int debugModeLoc;
	unsigned int hitBoxColorLoc;
};