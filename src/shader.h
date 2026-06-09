#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/util.h>

class Shader
{
public:
    Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
    ~Shader();
    void use();

    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
    void setMatrix44f(std::string name, glm::mat4 value);
    void setVec2f(std::string name, float x, float y);
    void setVec2f(std::string name, glm::vec2 value);
    void setVec3f(std::string name, float x, float y, float z);
    void setVec3f(std::string name, glm::vec3 value);
    void setVec4f(std::string name, float x, float y, float z, float w);
    void setVec4f(std::string name, glm::vec4 value);

	std::string getVertexPath();
	std::string getFragmentPath();
	std::string getGeometryPath();

	std::string getName();

	long getLastModificationVertexTime();
	long getLastModificationFragmentTime();
	long getLastModificationGeometryTime();
	void setLastModificationVertexTime(long lastModificationVertexTime);
	void setLastModificationFragmentTime(long lastModificationFragmentTime);
	void setLastModificationGeometryTime(long lastModificationGeometryTime);

private:
    GLuint id;
	std::string name;
    std::string vertexPath;
    std::string fragmentPath;
    std::string geometryPath;
	
	long lastModificationVertexTime;
	long lastModificationFragmentTime;
	long lastModificationGeometryTime;
    
    void compileShader();
};