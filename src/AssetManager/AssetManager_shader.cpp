#include "AssetManager.h"

namespace AssetManager {

Shader *GetShader(const std::string &shaderName) {
    auto &shaders = GetShaders();
    return shaders[shaderName].get();
}

Shader *AddShader(const std::string &shaderName, const ShaderSourcePaths &shaderSources) {
    auto &shaders = GetShaders();
    shaders[shaderName] = std::make_unique<Shader>(shaderSources.vertexPath,
                                                   shaderSources.fragmentPath,
                                                   shaderSources.geometryPath,
                                                   shaderSources.tessControlPath,
                                                   shaderSources.tessEvalPath);
    return shaders[shaderName].get();
}
} // namespace AssetManager
