#include "Navigator.h"

Navigator::Navigator(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    m_camera = Camera(position, up, yaw, pitch);
}

Camera &Navigator::GetCamera() { return m_camera; }
