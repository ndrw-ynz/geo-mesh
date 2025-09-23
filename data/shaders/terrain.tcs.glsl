#version 460 core

// Specify number of vertices per patch
layout(vertices = 4) out;

uniform mat4 model;
uniform mat4 view;

// Tessellation controls
uniform int uMinTessLevel;
uniform int uMaxTessLevel;
uniform float uMinLODDistance;
uniform float uMaxLODDistance;

// Input uv from vertex shader
in vec2 TexCoord[];
// Output uv to tessellation evaluation shader
out vec2 TextureCoord[];

float computeDistance(vec4 posEye, float minDist, float maxDist);
float computeTessLevel(float d0, float d1, int minLevel, int maxLevel);

void main() {
    // Passing vertex attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    TextureCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

    // Control tesselation levels for the entire patch w/ invocation 0
    if (gl_InvocationID == 0) {

        // ---------------------------------------
        // Implement LOD by patch based on tessellation parameters
        // Step 1: Setting parameters for controlling tessellation
        const int MIN_TESS_LEVEL = uMinTessLevel;
        const int MAX_TESS_LEVEL = uMaxTessLevel;
        const float MIN_DISTANCE = uMinLODDistance;
        const float MAX_DISTANCE = uMaxLODDistance;

        // Step 2: Transform each vertex of the patch into eye space
        vec4 eyeSpacePos00 = view * model * gl_in[0].gl_Position;
        vec4 eyeSpacePos01 = view * model * gl_in[1].gl_Position;
        vec4 eyeSpacePos10 = view * model * gl_in[2].gl_Position;
        vec4 eyeSpacePos11 = view * model * gl_in[3].gl_Position;

        // Step 3: Calculate and scale distance at [0,1]
        float distance00 = computeDistance(eyeSpacePos00, MIN_DISTANCE, MAX_DISTANCE);
        float distance01 = computeDistance(eyeSpacePos01, MIN_DISTANCE, MAX_DISTANCE);
        float distance10 = computeDistance(eyeSpacePos10, MIN_DISTANCE, MAX_DISTANCE);
        float distance11 = computeDistance(eyeSpacePos11, MIN_DISTANCE, MAX_DISTANCE);

        // Step 4: Interpolate edge tessellation level based on closer vertex
        float tessLevel0 = computeTessLevel(distance10, distance00, MIN_TESS_LEVEL, MAX_TESS_LEVEL);
        float tessLevel1 = computeTessLevel(distance00, distance01, MIN_TESS_LEVEL, MAX_TESS_LEVEL);
        float tessLevel2 = computeTessLevel(distance01, distance11, MIN_TESS_LEVEL, MAX_TESS_LEVEL);
        float tessLevel3 = computeTessLevel(distance11, distance10, MIN_TESS_LEVEL, MAX_TESS_LEVEL);

        // Step 5: Set outer edge tessellation levels
        gl_TessLevelOuter[0] = tessLevel0;
        gl_TessLevelOuter[1] = tessLevel1;
        gl_TessLevelOuter[2] = tessLevel2;
        gl_TessLevelOuter[3] = tessLevel3;

        // Step 6: Set inner edge tessellation levels
        gl_TessLevelInner[0] = max(tessLevel1, tessLevel3);
        gl_TessLevelInner[1] = max(tessLevel0, tessLevel2);
    }
}

float computeDistance(vec4 posEye, float minDist, float maxDist) {
    float d = clamp((abs(posEye.z) - minDist) / (maxDist - minDist), 0.0, 1.0);
    return d;
}
float computeTessLevel(float d0, float d1, int minLevel, int maxLevel) {
    float tessLevel = mix(maxLevel, minLevel, min(d0, d1));
    return tessLevel;
}
