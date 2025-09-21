#include "AssetManager.h"

namespace AssetManager {

Texture *AddTexture(const std::string &textureName, const std::string &texturePath) {
    int width, height, channels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return nullptr;
    }

    Texture texture{ width, height, data };
    stbi_image_free(data);

    auto &textures = GetTextures();
    auto [it, inserted] = textures.emplace(textureName, std::move(texture));

    if (!inserted) {
        std::cerr << "Warning: texture already exists: " << textureName << " (overwriting)\n";
        it->second = std::move(texture);
    }

    std::cout << "Loaded texture: " << textureName << " (" << width << "x" << height << ")\n";

    return &it->second;
}

Texture *GetTexture(const std::string &textureName) {
    auto &textures = GetTextures();
    return &textures[textureName];
}
} // namespace AssetManager
