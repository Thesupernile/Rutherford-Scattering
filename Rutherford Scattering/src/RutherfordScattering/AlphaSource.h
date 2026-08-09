#pragma once
#include "Particle.h"

namespace RutherfordScattering {
	class AlphaSource : public DrawableObject {
	private:
		float _gapWidth;		// Width of the opening in the source (affets emission rate)
		float _sourceSpread;	// The range of angles a particle can be emitted at
		int _emissionRate;		// How many alpha particles the source emits per second

		VertexBuffer vb;
		VertexArray va;
		IndexBuffer ib;

		Shader shader;
		std::string shaderFilePath = "res/shaders/particle.shader";
		Texture texture;
		VertexBufferLayout layout;

		std::vector<objectVertex> objectVertices;
		std::vector<objectIndex> objectIndexes;

		int numVerticesPerObject;

		void GenerateObjectVertices();
		void GenerateObjectIndicies();
	public:
		AlphaSource();
		~AlphaSource();
		AlphaSource(const AlphaSource& oldObject);

		void IncrementFrame() override;

		void SetEmissionRate(int newEmissionRate);
		int GetEmissionRate();

		void SetAngle(float newAngle);
		float GetAngle();

		void SetSourceSpread(float newSourceSpread) { _sourceSpread = newSourceSpread; }
		float GetSourceSpread() { return _sourceSpread; }

		void Draw(glm::mat4& VPMatrix, Renderer& renderer) override;
	};
}