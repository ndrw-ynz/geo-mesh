#version 460 core

#ifndef MAX_BIOMES
#define MAX_BIOMES 5
#endif

uniform int renderMode;

uniform int uNumBiomes;
uniform float uBiomeHeights[MAX_BIOMES];
uniform vec3 uBiomeColors[MAX_BIOMES];

// Lighting Uniforms
uniform vec3 uLightColor;
uniform float uAmbientStrength;
uniform float uSpecularStrength;
uniform vec3 uLightDir;
uniform vec3 uViewPos;

out vec4 FragColor;

in float Height;
in vec3 Normal;

void main()
{
    float h = (Height + 16) / 64.0f; // shift and scale the height into a grayscale value

    vec3 color;
    switch (renderMode) {
        case 0:
        default:
        // Grayscale
        color = vec3(h, h, h);
        break;
        case 1:
        // Biome coloring
        vec3 biomeColor = uBiomeColors[0];
        for (int i = 0; i < uNumBiomes; i++) {
            if (h < uBiomeHeights[i]) {
                biomeColor = uBiomeColors[i];
                break;
            }
        }
        color = biomeColor;
        break;
    }

    // Lambertian Shading
    // ---- Ambient
    vec3 ambient = uAmbientStrength * uLightColor;

    // ---- Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-uLightDir);
    float diffuseFactor = max(dot(norm, lightDir), 0);
    vec3 diffuse = diffuseFactor * uLightColor;

    FragColor = vec4((ambient + diffuse) * color, 1.0);
    // FragColor = vec4(color, 1.0);
}
