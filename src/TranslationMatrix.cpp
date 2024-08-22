#include "TranslationMatrix.hpp"

TranslationMatrix::TranslationMatrix(float delX, float delY, float delZ)
{
    m_translationMatrix = glm::mat4{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, delX, delY, delZ, 1.0f};
}

const float *TranslationMatrix::operator&() const
{
    return glm::value_ptr(m_translationMatrix);
}
