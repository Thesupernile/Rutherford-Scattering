#pragma once
namespace RutherfordScattering {
	struct Constants {
		// Universal Constants
		float permitivityOfFreeSpace;
		float hydrogenRadius;
		float nucleonMass;
		float atomicRadiusMultiplier;

		// Simulation Constants
		float simulationScaleFactor = 7e9f;
		float simulationTimeFactor = 1e-3f;

		// Foil Constants
		int foilWidth = 3;
		int foilLength = 75;
	};
}