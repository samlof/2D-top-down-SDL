#include "Graphics\GLSLProgram.h"

#include <fstream>
#include <vector>


namespace Graphics {
	GLSLProgram::GLSLProgram()
		:
		mProgramId(0), mVertexShaderId(0), mFragmentShaderId(0), mNumAttributes(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string & pVertexShaderFilePath, const std::string & pFragmentShaderFilePath)
	{
		mProgramId = glCreateProgram();

		mVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		if (mVertexShaderId == 0) {
			printf("Vertex shader creation failed!\n");
		}
		mFragmentShaderId = glCreateShader(GL_VERTEX_SHADER);
		if (mFragmentShaderId == 0) {
			printf("mFragmentShaderId creation failed!\n");
		}

		compileShader(pVertexShaderFilePath, mVertexShaderId);
		compileShader(pFragmentShaderFilePath, mFragmentShaderId);
	}

	void GLSLProgram::linkShaders()
	{

		//Attach our shaders to our program
		glAttachShader(mProgramId, mVertexShaderId);
		glAttachShader(mProgramId, mFragmentShaderId);

		//Link our program
		glLinkProgram(mProgramId);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(mProgramId, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(mProgramId, maxLength, &maxLength, &errorLog[0]);

			printf("Error in linking shaders\n");
			printf(&("%s\n", errorLog[0]));

			//We don't need the program anymore.
			glDeleteProgram(mProgramId);
			//Don't leak shaders either.
			glDeleteShader(mVertexShaderId);
			glDeleteShader(mFragmentShaderId);

			//Use the infoLog as you see fit.

			//In this simple program, we'll just leave
			return;
		}

		//Always detach shaders after a successful link.
		glDetachShader(mProgramId, mVertexShaderId);
		glDetachShader(mProgramId, mFragmentShaderId);
		glDeleteShader(mVertexShaderId);
		glDeleteShader(mFragmentShaderId);
	}

	void GLSLProgram::addAttribute(const std::string & pAttributeName)
	{
		glBindAttribLocation(mProgramId, mNumAttributes++, pAttributeName.c_str());
	}

	GLint Graphics::GLSLProgram::getUniformLocation(const std::string & pUniformName)
	{
		GLint location = glGetUniformLocation(mProgramId, pUniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			printf("Uniform \"%s\" location not found!", pUniformName.c_str());
		}
		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(mProgramId);
		for (int i = 0; i < mNumAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < mNumAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const std::string & pFilePath, GLuint pShaderId)
	{
		std::ifstream file(pFilePath);
		if (file.fail()) {
			printf("Failed to open: %s\n", pFilePath.c_str());
		}
		std::string fileContents;
		std::string line;
		while (std::getline(file, line)) {
			fileContents += line + "\n";
		}
		file.close();

		const char* filePtr = fileContents.c_str();
		glShaderSource(pShaderId, 1, &filePtr, nullptr);

		glCompileShader(pShaderId);

		GLint isCompiled = 0;
		glGetShaderiv(pShaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(pShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(pShaderId, maxLength, &maxLength, &errorLog[0]);
			printf("Error in compiling: %s\n", pFilePath.c_str());
			printf(&("%s\n", errorLog[0]));
			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(pShaderId); // Don't leak the shader.
			return;
		}
	}
}