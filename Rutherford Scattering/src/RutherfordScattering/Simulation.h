#pragma once
#include "Constants.h"
#include "Particle.h"
#include "AlphaSource.h"

#include <vector>

namespace RutherfordScattering {
	static class Simulation {
	private:
		std::vector<AlphaSource> _alphaSources = std::vector<AlphaSource>();
		std::list<Particle> _particles = std::list<Particle>();

		void CreateFoil();
		void CreateAlphaSources();

		void ProcessAlphaEmissions();
		void ProcessParticleMovement();
		void ProcessElectrostaticForces();
	public:
		Constants constants;

		Simulation();
		~Simulation();


		void ProcessSimulationFrame();
		void SetNewConstants(Constants newConstants);
		void DrawElements(glm::mat4& VP, Renderer& renderer);
	};
}