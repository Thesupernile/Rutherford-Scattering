#include "DrawableObject.h"

DrawableObject::DrawableObject(const void* vertexData, const VertexBufferLayout& vertexLayout, unsigned int* indexData, std::string& shaderFilePath, std::string& textureFilePath)
: layout(vertexLayout), vb(VertexBuffer(vertexData, sizeof(vertexData))), ib(IndexBuffer(indexData, sizeof(*indexData) / sizeof((&indexData)[0]))), shader(Shader(shaderFilePath)), texture(Texture(textureFilePath))
{
	va.AddBuffer(vb, layout);
}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::SetPos(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void DrawableObject::Draw(glm::mat4 VPMatrix, Renderer& renderer)
{
	va.Bind();
	shader.Bind();
	texture.Bind();

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 MVP = VPMatrix * modelMatrix;

	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("u_Colour", 0.0f, 0.0f, 0.0f, 0.0f);
	shader.SetUniformMat4f("u_MVP", MVP);

	renderer.Draw(va, ib, shader);
}
