#include "IndexBuffer.h"
#include "Renderer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))

    glGenBuffers(1, &m_RendereID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendereID);
}



void IndexBuffer::Bind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendereID);
}

void IndexBuffer::Unbind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
