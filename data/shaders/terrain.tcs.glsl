#version 460 core

// Specify number of vertices per patch
layout(vertices = 4) out;

// Input uv from vertex shader
in vec2 TexCoord[];
// Output uv to tessellation evaluation shader
out vec2 TextureCoord[];

void main() {
    // Passing vertex attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    TextureCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

    // Control tesselation levels for the entire patch w/ invocation 0
    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = 16;
        gl_TessLevelOuter[1] = 16;
        gl_TessLevelOuter[2] = 16;
        gl_TessLevelOuter[3] = 16;

        gl_TessLevelInner[0] = 16;
        gl_TessLevelInner[1] = 16;
    }
}
