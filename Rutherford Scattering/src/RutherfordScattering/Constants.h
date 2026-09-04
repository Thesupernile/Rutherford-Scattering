#pragma once

// Include glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <thread>

namespace RutherfordScattering {
	struct Constants {
		// Universal Constants
		float PI = 3.141592;
		float permitivityOfFreeSpace = 8.85e-12;
		float hydrogenRadius = 1.2e-15;
		float nucleonMass = 1.67e-27;
		float atomicRadiusMultiplier = 1e5;
		float protonCharge = 1.6e-19;

		float GetElectrostaticConstant() { return 1 / (4 * PI * permitivityOfFreeSpace); }

		// Alpha Particle Constants
		int numProtonsPerAlpha = 2;
		int numNeutronsPerAlpha = 2;
		bool flipParticleCharge = false;
		float alphaParticleInitialSpeed = 1.5e7f;

		// Alpha Source Constants
		glm::vec3 alphaSourcePos = glm::vec3({0, 350, 0});
		float alphaSourceAngle = 0;
		float alphaSourceAngleRads() { return (alphaSourceAngle / 360) * 2 * PI; }
		float alphaSourceSpread = 1;
		float alphaSourceSpreadRads() { return (alphaSourceSpread / 360) * 2 * PI; }
		float alphaSourceEmissionRate = 0.5;

		// Simulation Constants
		float simulationScaleFactor = 7e9f;
		float simulationTimeFactor = 1.5e-7f;
		float expectedMilisecsPerFrame = 16.666667;		// This represents a standard framerate of 60fps
		int maxNumThreads = std::thread::hardware_concurrency();

		int defaultParticleTTL = 120;

		// Foil Constants
		int foilWidth = 1;
		int foilLength = 75;
		glm::vec3 foilPos = glm::vec3({400, 0, 0});
	};
}