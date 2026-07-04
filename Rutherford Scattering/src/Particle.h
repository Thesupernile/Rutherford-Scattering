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

		int protonNumber;
		int nucleonNumber;
		Constants& constants;

		glm::vec3 velocity = glm::vec3(0, 0, 0);

		void generateParticleVertexes();
		void generateParticleIndexes();

	public:
		Particle(int protonNumber, int nucleonNumber, Constants& constants);
		~Particle();

		void incrementFrame() override;

		void processElectromagneticForces(glm::vec3 particlePosition, int particleCharge);
	};

}