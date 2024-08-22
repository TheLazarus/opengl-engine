#include "PerspectiveMatrix.hpp"

PerspectiveMatrix::PerspectiveMatrix(float near, float far, float left, float right, float top, float bottom)
{
    m_perspectiveMatrix = glm::mat4{2 * (near / (right - left)), 0.0f, 0.0f, 0.0f, 0.0f, 2 * (near / (top - bottom)), 0.0f, 0.0f, (right + left) / (right - left), (top + bottom) / (top - bottom), -((far + near) / (far - near)), -1.0f, 0.0f, 0.0f, (-2 * far * near) / (far - near), 0.0f};
}

const float *PerspectiveMatrix::operator&() const
{
    return glm::value_ptr(m_perspectiveMatrix);
}
