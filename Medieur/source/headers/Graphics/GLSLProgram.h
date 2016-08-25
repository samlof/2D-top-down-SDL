#pragma once

#include <string>
#include <GL\glew.h>

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void linkShaders();
private:
	GLuint mProgramId;
};