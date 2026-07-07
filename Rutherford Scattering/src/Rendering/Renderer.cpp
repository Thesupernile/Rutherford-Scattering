#include "Renderer.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    // Self Note: This works until error is zero (therefore until all errors are cleared)
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] Error Code: " << error << "\nFunction: " << function << " \nLine: " << line << " \nFile: " << file << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    // Nullptr allowed since index buffer has already been bound
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
