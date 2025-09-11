#pragma once

#include <glm/glm.hpp>

struct Vertex {
    Vertex() = default;
    Vertex(glm::vec3 pos = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0), glm::vec3 norm = glm::vec3(0))
        : position{ pos }, uv{ texCoord }, normal{ norm } {}

    glm::vec3 position = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 normal = glm::vec3(0);
};
