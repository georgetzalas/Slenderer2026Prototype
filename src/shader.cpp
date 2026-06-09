#include "shader.h"
#include <iostream>

Shader::Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
	this->name = Util::GetFileNameFromPath(vertexPath);

	this->vertexPath = vertexPath; 
	this->fragmentPath = fragmentPath; 
	this->geometryPath = geometryPath; 

	compileShader();
}

Shader::~Shader()
{
    glDeleteShader(id);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::compileShader()
{
    int  success;
    char infoLog[512];

    std::string vertexCode = Util::ReadFileContents(vertexPath);
    std::string fragmentCode = Util::ReadFileContents(fragmentPath);
    std::string geometryCode = "";

    if(geometryPath != "")
        geometryCode = Util::ReadFileContents(geometryPath);

    //VERTEX//

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCCode = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexCCode, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //FRAGMENT//
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentCCode = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentCCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //GEOMETRY//
    GLuint geometryShader;
    if(geometryPath != "")
    {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

        const char* geometryCCode = geometryCode.c_str();
        glShaderSource(geometryShader, 1, &geometryCCode, NULL);
        glCompileShader(geometryShader);

        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    if(geometryPath != "") glAttachShader(id, geometryShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(geometryPath != "") glDeleteShader(geometryShader);
}

void Shader::setBool(std::string name, bool value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(std::string name, int value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(std::string name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMatrix44f(std::string name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec2f(std::string name, float x, float y)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Shader::setVec2f(std::string name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setVec3f(std::string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::setVec3f(std::string name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4f(std::string name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::setVec4f(std::string name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

std::string Shader::getName()
{
	return this->name;
}

std::string Shader::getVertexPath()
{
	return vertexPath;
}

std::string Shader::getFragmentPath()
{
	return fragmentPath;
}

std::string Shader::getGeometryPath()
{
	return geometryPath;
}

long Shader::getLastModificationVertexTime()
{
	return lastModificationVertexTime;
}

long Shader::getLastModificationFragmentTime()
{
	return lastModificationFragmentTime;
}

long Shader::getLastModificationGeometryTime()
{
	return lastModificationGeometryTime;
}

void Shader::setLastModificationVertexTime(long lastModificationVertexTime)
{
	this->lastModificationVertexTime = lastModificationVertexTime;
}

void Shader::setLastModificationFragmentTime(long lastModificationFragmentTime)
{
	this->lastModificationFragmentTime = lastModificationFragmentTime;
}

void Shader::setLastModificationGeometryTime(long lastModificationGeometryTime)
{
	this->lastModificationGeometryTime = lastModificationGeometryTime;
}
