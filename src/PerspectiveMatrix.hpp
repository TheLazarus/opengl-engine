#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class PerspectiveMatrix
{
    float near{}, far{}, left{}, right{}, top{}, bottom{};
    glm::mat4 m_perspectiveMatrix;

public:
    PerspectiveMatrix(float near, float far, float left, float right, float top, float bottom);

    const float *operator&() const;
};