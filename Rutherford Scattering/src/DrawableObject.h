#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>

class DrawableObject {
private:
	VertexBuffer vb;
	VertexArray va;
	VertexBufferLayout layout;
	IndexBuffer ib;

	Shader shader;
	Texture texture;

	glm::vec3 position;
public:
	DrawableObject(const void* vertexData, const VertexBufferLayout& vertexLayout, unsigned int* indexData, std::string& shaderFilePath, std::string& textureFilePath);
	~DrawableObject();

	virtual void incrementFrame() = 0;

	void SetPos(float x, float y, float z);
	void Draw(glm::mat4 VPMatrix, Renderer& renderer);
};