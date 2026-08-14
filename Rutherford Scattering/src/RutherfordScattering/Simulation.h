#pragma once
#include "Constants.h"
#include "Particle.h"
#include "AlphaSource.h"

#include <vector>
#include <cmath>
#include <thread>
#include <iostream>
#include <mutex>

namespace RutherfordScattering {
	static class Simulation {
	private:
		int currentParticle = 0;
		std::list<Particle>::iterator particleIterator;
		std::mutex* particleMutex;

		float PI = 3.141592;
		std::vector<AlphaSource> _alphaSources = std::vector<AlphaSource>();
		std::list<Particle> _particles = std::list<Particle>();
		Constants constants;

		void CreateFoil();
		void CreateAlphaSources();

		void ProcessAlphaEmissions();
		void ProcessParticleMovement();

		void ProcessParticleForcesOneThread();
		void ProcessElectrostaticForces();
	public:
		Simulation();
		~Simulation();


		void ProcessSimulationFrame();
		Constants* GetConstantsPtr();
		void DrawElements(glm::mat4& VP, Renderer& renderer);
	};
}