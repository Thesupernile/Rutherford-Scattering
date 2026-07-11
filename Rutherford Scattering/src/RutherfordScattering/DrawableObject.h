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

namespace RutherfordScattering {
	class DrawableObject {
	private:
		VertexBuffer vb;
		VertexArray va;
		IndexBuffer ib;

		Shader shader;
		Texture texture;

	protected:
		const float PI = 3.1415926;

		VertexBufferLayout layout;
		glm::vec3 _position = glm::vec3(0, 0, 0);
		float _rotation = 0;
		float _scale = 10;

		struct objectVertex {
			float x;
			float y;
			float u;
			float v;
		};
		std::vector<objectVertex> objectVertices;

		// One "index" represents one triangle
		std::vector<objectIndex> objectIndexes;

		int numVerticesPerObject;

		std::string shaderFilePath = "res/shaders/particle.shader";
		std::string textureFilePath = "res/textures/emptyTexture.png";

		void SetVertexBufferData(const void* data, unsigned int size);
		void SetIndexBufferData(unsigned int* data, unsigned int count);
		void SetShader(std::string path);
		void SetTexture(std::string path);

		std::vector<unsigned int> ParseIndices(std::vector<objectIndex> data);
	public:
		DrawableObject();
		~DrawableObject();
		DrawableObject(const DrawableObject& oldObject);

		virtual void incrementFrame() = 0;

		void SetPos(float x, float y, float z);
		void Draw(glm::mat4& VPMatrix, Renderer& renderer);
	};
}