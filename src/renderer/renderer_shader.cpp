	#include <renderer_shader.h>


Shader::Shader(): ResourceManager()
{
}

Shader::~Shader()
{

}


GLuint Shader::compileShaderFromFilepath(const char* filepath, /*std::vector<std::string> locations,*/ GLenum type)
{
	/* Read the file contents */
	auto source = read_string_from_file(filepath);
	//remembering a set of locations:
	//this->locations = locations;
	/* Use other function to compile the extracted source, then clean up and return */
	GLuint shader = compileShader(source.c_str(), type);

	return shader;
}

GLuint Shader::compileShader(const char* source, GLenum type)
{
	/* Create shader, attach source code and compile it */
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);
	
	/* Check for errors */
	if (!this->returnShaderCompileStatus(shaderID))
	{
		std::cout << "Couldn't compile one of the shaders\n";
		glDeleteShader(shaderID);
		//Delete and returns an invalid GL ID:

		return 0;
	}
	//Append the shaderID to the vector of shaders in the object:
	compiledShaderListID.insert(compiledShaderListID.end(), shaderID);
	return shaderID;
}

GLuint Shader::createProgram()
{
	/* Create program */
	this->programID = glCreateProgram();

	/* Attach all shaders that should be part of the program */
	for (auto shader : compiledShaderListID)
	{
		glAttachShader(this->programID, shader);
	}



	/* Link the program */
	glLinkProgram(programID);

	//Check for errors:
	if (!this->returnProgramLinkStatus(programID))
	{
		std::cout << "Shader::create_program() Couldn't link shaders\n";
		//Delete and returns an invalid GL ID:
		glDeleteProgram(programID);
		//Delete all the shaders:
		clearCompiledShaders();
		return 0;
	}
	std::cout << "program " << this->programID << " created\n";

	clearCompiledShaders();
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	std::cout << "current program:" << id << " - while gl_fragment_shader_program is:" << this->programID;
	glUseProgram(this->programID);
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	std::cout << "current program:" << id << " - while gl_fragment_shader_program is:" << this->programID;

	return programID;

}

//Deletes all unused shaders:
void Shader::clearCompiledShaders() {
	//Iterate through compiled_shader list:
	for (auto i : compiledShaderListID)
	{
		//delete set compiled_shader:
		glDeleteShader(i);
	}
	//Clears the vector list:
	compiledShaderListID.clear();
}


//myCheckShaderStatus checks if the compilation of a shader code was succsessfull.
//if it fails it prints out an error message:
bool Shader::returnShaderCompileStatus(GLuint& shaderID) {
	GLint myCompileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &myCompileStatus);

	//ERRORHANDLING:
	if (myCompileStatus != GL_TRUE)
	{
		GLint myInfoLogLenght;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &myInfoLogLenght);
		GLchar* buffer = new GLchar[myInfoLogLenght];

		GLsizei myBufferSize; //GLsizei is an int...
		glGetShaderInfoLog(shaderID, myInfoLogLenght, &myBufferSize, buffer);
		std::cout << buffer << std::endl;

		delete[] buffer;
		return false;
	}
	return true;

}
//myCheckProgramLinkStatus checks if the shaders were able to link.
//if it fails it prints out an error message:
bool Shader::returnProgramLinkStatus(GLuint& programID) {
	GLint myLinkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &myLinkStatus);

	//ERRORHANDLING:
	if (myLinkStatus != GL_TRUE)
	{
		GLint myInfoLogLenght;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &myInfoLogLenght);
		GLchar* buffer = new GLchar[myInfoLogLenght];

		GLsizei myBufferSize; //GLsizei is an int...
		glGetProgramInfoLog(programID, myInfoLogLenght, &myBufferSize, buffer);
		std::cout << buffer << std::endl;

		delete[] buffer;

		return false;
	}
	return true;
}


Shader& Shader::bindShaderProgram()
{
	//GLint id;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	//std::cout << "current program:" << id << " - while gl_fragment_shader_program is:" << this->programID;
	glUseProgram(this->programID);
	//glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	//std::cout << "current program:" << id << " - while gl_fragment_shader_program is:" << this->programID;
	return *this;
}




void Shader::deleteShaderProgram() 
{
	clearCompiledShaders();
	glDeleteProgram(programID);
}


#pragma region set_uniform_values


void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform1f(glGetUniformLocation(this->programID, name), value);
}
void Shader::setInt(const GLchar* name, GLint value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform1i(glGetUniformLocation(this->programID, name), value);
}
void Shader::setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform2f(glGetUniformLocation(this->programID, name), x, y);
}
void Shader::setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform2f(glGetUniformLocation(this->programID, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform3f(glGetUniformLocation(this->programID, name), x, y, z);
}
void Shader::setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform3f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform4f(glGetUniformLocation(this->programID, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform4f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
	{
		this->bindShaderProgram();
	}
	auto location = glGetUniformLocation(this->programID, name);
	if (location < 0)
	{
		std::cout << "SetMatrix4() couldn't get uniform location of: " << name << std::endl;
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		std::cout << "current program:" << id << " - while gl_fragment_shader_program is:" << this->programID;
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

}


void    Shader::setFloat(const unsigned location, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform1f(location, value);

}
void    Shader::setInt(const unsigned location, GLint value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform1i(location, value);

}
void    Shader::setVector2f(const unsigned location, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform2f(location, x, y);
}
void    Shader::setVector2f(const unsigned location, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform2f(location, value.x, value.y);

}
void    Shader::setVector3f(const unsigned location, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform3f(location, x, y, z);
}
void    Shader::setVector3f(const unsigned location, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform3f(location, value.x, value.y, value.z);

}
void    Shader::setVector4f(const unsigned location, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniform4f(location, x, y, z, w);
}
void    Shader::setVector4f(const unsigned location, const glm::vec4& value, GLboolean useShader) 
{
	if (useShader)
		this->bindShaderProgram();
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
void    Shader::setMatrix4(const unsigned location, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
void    Shader::setMatrix3(const unsigned location, const glm::mat3& matrix, GLboolean useShader)
{
	if (useShader)
		this->bindShaderProgram();
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
#pragma endregion