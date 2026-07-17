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

		void generateObjectVertices();
		void generateObjectIndicies();
	public:
		AlphaSource();
		~AlphaSource();
		AlphaSource(const AlphaSource& oldObject);

		void incrementFrame() override;

		void setEmissionRate(int newEmissionRate);
		int getEmissionRate();

		void setAngle(float newAngle);
		int getAngle();

		float getSourceSpread() { return _sourceSpread; }
	};
}