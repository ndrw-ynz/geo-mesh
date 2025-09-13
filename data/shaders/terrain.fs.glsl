#version 460 core

#ifndef MAX_BIOMES
#define MAX_BIOMES 5
#endif

uniform int renderMode;

uniform int uNumBiomes;
uniform float uBiomeHeights[MAX_BIOMES];
uniform vec3 uBiomeColors[MAX_BIOMES];

out vec4 FragColor;

in float Height;

void main()
{
    float h = (Height + 16) / 64.0f; // shift and scale the height into a grayscale value

    switch (renderMode) {
        case 0:
        default:
        // Grayscale
        FragColor = vec4(h, h, h, 1.0);
        break;
        case 1:
        // Biome coloring
        vec3 color = uBiomeColors[0];
        for (int i = 0; i < uNumBiomes; i++) {
            if (h < uBiomeHeights[i]) {
                color = uBiomeColors[i];
                break;
            }
        }
        FragColor = vec4(color, 1.0);
        break;
    }
}
