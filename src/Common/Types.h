#pragma once
#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <optional>
#include <string>

struct Vertex {
    Vertex() = default;
    Vertex(glm::vec3 pos = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0), glm::vec3 norm = glm::vec3(0))
        : position{ pos }, uv{ texCoord }, normal{ norm } {}

    glm::vec3 position = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
    glm::vec3 normal = glm::vec3(0);
};

struct Vertex2D {
    Vertex2D() = default;
    Vertex2D(glm::vec2 pos = glm::vec2(0), glm::vec2 texCoord = glm::vec2(0)) : position{ pos }, uv{ texCoord } {}

    glm::vec2 position = glm::vec2(0);
    glm::vec2 uv = glm::vec2(0);
};
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

struct ShaderSourcePaths {
    std::string vertexPath;
    std::string fragmentPath;
    std::optional<std::string> geometryPath;
    std::optional<std::string> tessControlPath;
    std::optional<std::string> tessEvalPath;
};
