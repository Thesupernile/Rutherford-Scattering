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
		float alphaParticleInitialSpeed = 1.5e7f;

		// Simulation Constants
		float simulationScaleFactor = 7e9f;
		float simulationTimeFactor = 3e-7f;

		int defaultParticleTTL = 400;

		// Foil Constants
		int foilWidth = 2;
		int foilLength = 75;
	};
}