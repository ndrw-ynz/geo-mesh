#include "Renderer.h"

namespace Renderer {

void InitText() {
    Shader *textShader = AssetManager::GetShader("textShader");

    textShader->use();
    glm::mat4 textProjection =
        glm::ortho(0.0f, (float)GLFWIntegration::GetWindowWidth(), 0.0f, (float)GLFWIntegration::GetWindowHeight());
    textShader->setMat4("projection", textProjection);
}

void TextPass() {
    glDisable(GL_DEPTH_TEST);
    Mesh2D &textMesh = TextUI::GetTextUI();

    Shader &textShader = *AssetManager::GetShader("textShader");
    RenderText(textShader,
               textMesh.GetMesh2DBuffer(),
               "FPS: " + std::to_string(World::GetFPS()),
               15.0f,
               15.0f,
               1.0f,
               glm::vec3(0.5, 0.8f, 0.2f));
}

void RenderText(
    Shader &shader, Mesh2DBuffer &textMesh2DBuffer, std::string text, float x, float y, float scale, glm::vec3 color) {
    // avoid rendering text as wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // activate corresponding render state
    float copyX = x;
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textMesh2DBuffer.GetVAO());

    // iterate through all characters
    std::array<Character, 128> Characters = AssetManager::GetFont("IBM VGA 8x16"); // TEMPORARY HERE.. FOR TEST

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];
        if (*c == 'n') {
            y -= ((ch.Size.y)) * 1.3 * scale;
            x = copyX;
        } else if (*c == ' ') {
            x += (ch.Advance >> 6) * scale;
        } else {

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            std::vector<Vertex2D> vertices = { Vertex2D{ glm::vec2(xpos, ypos + h), glm::vec2(0.0f, 0.0f) },
                                               Vertex2D{ glm::vec2(xpos, ypos), glm::vec2(0.0f, 1.0f) },
                                               Vertex2D{ glm::vec2(xpos + w, ypos), glm::vec2(1.0f, 1.0f) },
                                               Vertex2D{ glm::vec2(xpos, ypos + h), glm::vec2(0.0f, 0.0f) },
                                               Vertex2D{ glm::vec2(xpos + w, ypos), glm::vec2(1.0f, 1.0f) },
                                               Vertex2D{ glm::vec2(xpos + w, ypos + h), glm::vec2(1.0f, 0.0f) } };
            float v[6][4] = { { xpos, ypos + h, 0.0f, 0.0f },    { xpos, ypos, 0.0f, 1.0f },
                              { xpos + w, ypos, 1.0f, 1.0f },

                              { xpos, ypos + h, 0.0f, 0.0f },    { xpos + w, ypos, 1.0f, 1.0f },
                              { xpos + w, ypos + h, 1.0f, 0.0f } };

            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, textMesh2DBuffer.GetVBO());
            textMesh2DBuffer.UpdateBuffers(vertices);
            // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th
                                            // pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
// render line of text

} // namespace Renderer
