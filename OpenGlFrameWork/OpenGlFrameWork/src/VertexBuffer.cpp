#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendereID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendereID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendereID);
}



void VertexBuffer::Bind()const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendereID);
}

void VertexBuffer::Unbind()const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
