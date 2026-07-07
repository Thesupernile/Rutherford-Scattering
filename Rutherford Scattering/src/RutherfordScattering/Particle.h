#pragma once
#include "DrawableObject.h"
#include "Constants.h"

#include <string>
#include <memory>

namespace RutherfordScattering {

	class Simulation;

	class Particle : public DrawableObject {
	private:
		static constexpr float PI = 3.141592;

		int _protonNumber;
		int _nucleonNumber;
		bool _isMovable;
		Constants& _constants;

		glm::vec3 _velocity = glm::vec3(0, 0, 0);

		void generateParticleVertexes();
		void generateParticleIndexes();

		void calculateScale();

	public:
		Particle(int protonNumber, int nucleonNumber, Constants& constants);
		Particle(const Particle& oldParticle);
		~Particle();

		void incrementFrame() override;
		bool isMovable();
		int getNuclearRadius();
		int getAtomicRadius();

		void processElectromagneticForces(glm::vec3 particlePosition, int particleCharge);
	};

}