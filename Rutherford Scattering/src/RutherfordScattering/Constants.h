#pragma once

// Include glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RutherfordScattering {
	struct Constants {
		// Universal Constants
		float PI = 3.141592;
		float permitivityOfFreeSpace = 8.85e-12;
		float hydrogenRadius;
		float nucleonMass;
		float atomicRadiusMultiplier;
		float protonCharge = 1.6e-19;

		float GetElectrostaticConstant() { return 1 / (4 * PI * permitivityOfFreeSpace); }

		// Alpha Particle Constants
		int numProtonsPerAlphaSource = 2;
		int numNeutronsPerAlphaSource = 2;
		float alphaParticleInitialSpeed = 1.5e7f;

		// Alpha Source Constants
		glm::vec3 alphaSourcePos = glm::vec3({0, 350, 0});
		float alphaSourceAngle = 0;

		// Simulation Constants
		float simulationScaleFactor = 7e9f;
		float simulationTimeFactor = 3e-7f;

		int defaultParticleTTL = 350;

		// Foil Constants
		int foilWidth = 2;
		int foilLength = 75;
	};
}