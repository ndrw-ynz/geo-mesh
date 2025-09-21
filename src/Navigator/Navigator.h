#pragma once
#include "Graphics/Camera.h"

class Navigator {
  public:
    Navigator() = default;
    Navigator(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    Camera &GetCamera();

  private:
    Camera m_camera{};
};
