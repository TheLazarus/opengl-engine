#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TranslationMatrix
{

    glm::mat4 m_translationMatrix;

public:
    TranslationMatrix(float delX, float delY, float delZ);

    const float *operator&() const;
};