#pragma once
#include "Particle.h"

namespace RutherfordScattering {
	class AlphaSource : public DrawableObject {
	private:
		float _angle;			// Angle of orientation of the alpha source (0 degrees points right)
		float _gapWidth;		// Width of the opening in the source (affets emission rate)
		float _sourceSpread;	// The range of angles a particle can be emitted at
		int _emissionRate;		// How many alpha particles the source emits per second

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
		int GetAngle();

		float GetSourceSpread() { return _sourceSpread; }
	};
}