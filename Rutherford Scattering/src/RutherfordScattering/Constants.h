#pragma once
namespace RutherfordScattering {
	struct Constants {
		// Universal Constants
		float permitivityOfFreeSpace;
		float hydrogenRadius;
		float nucleonMass;
		float atomicRadiusMultiplier;
		float protonCharge = 1.6e-19;

		// Alpha Particle Constants
		int numProtonsPerAlphaSource = 2;
		int numNeutronsPerAlphaSource = 2;
		float alphaParticleInitialSpeed = 5;

		// Simulation Constants
		float simulationScaleFactor = 7e9f;
		float simulationTimeFactor = 1e-3f;

		int defaultParticleTTL = 300;

		// Foil Constants
		int foilWidth = 2;
		int foilLength = 75;
	};
}