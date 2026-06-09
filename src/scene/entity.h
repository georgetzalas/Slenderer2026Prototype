#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils/types.h>

typedef uint64_t EntityID;

struct TransformComponent
{
    glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale    = glm::vec3(1);

    TransformComponent() = default;

	glm::mat4 toMat4() const 
	{
		glm::mat4 m = glm::translate(glm::mat4(1), position);
		m *= glm::mat4_cast(glm::quat(rotation));
		m = glm::scale(m, scale);
		return m;
	};
};

struct Entity
{
    EntityID id;
    std::string name;
    TransformComponent transformComponent;
    Model* model;
};