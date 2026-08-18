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
	protected:
		const float PI = 3.1415926;

		glm::vec3 _position = glm::vec3(0, 0, 0);
		glm::vec3 _oldPosition = glm::vec3(0, 0, 0);
		glm::vec4 _colour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		float _rotation = 0;
		float _scale = 10;

		struct objectVertex {
			float x;
			float y;
			float u;
			float v;
		};
		//std::vector<objectVertex>* pObjectVertices;

		// One "index" represents one triangle
		//std::vector<objectIndex>* pObjectIndexes;

		std::string textureFilePath = "res/textures/emptyTexture.png";

		static void SetVertexBufferData(const void* data, unsigned int size, VertexBuffer& vb, VertexArray& va, VertexBufferLayout& layout);
		static void SetIndexBufferData(unsigned int* data, unsigned int count, IndexBuffer& ib);
		static void SetShader(std::string path, Shader& shader);
		static void SetTexture(std::string path, Texture& texture);

		static std::vector<unsigned int> ParseIndices(std::vector<objectIndex> data);
	public:
		DrawableObject();
		~DrawableObject();
		DrawableObject(const DrawableObject& oldObject);

		virtual void IncrementFrame(float delta) = 0;

		void SetPos(glm::vec3 newPosition);
		glm::vec3 GetPos();
		glm::vec3 GetPreviousPos();
		float GetScale();
		void DrawObject(glm::mat4& VPMatrix, Renderer& renderer, VertexArray& va, IndexBuffer& ib, Shader& shader);
		virtual void Draw(glm::mat4& VPMatrix, Renderer& renderer) = 0;
	};
}