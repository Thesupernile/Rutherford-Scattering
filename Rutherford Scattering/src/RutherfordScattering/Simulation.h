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
		int _currentParticle = 0;
		int _numParticlesSimulated = 0;
		int _numParticlesDeflected = 0;
		int _numParticlesBackscattered = 0;
		std::list<Particle>::iterator _particleIterator;
		std::mutex* _particleMutex;

		float PI = 3.141592;
		std::vector<AlphaSource> _alphaSources = std::vector<AlphaSource>();
		std::list<Particle> _particles = std::list<Particle>();
		Constants _constants;

		void CreateFoil();
		void CreateAlphaSources();

		void ProcessAlphaEmissions(float delta);
		void ProcessParticleMovement(float delta);

		void ProcessParticleForcesOneThread(float delta);
		void ProcessElectrostaticForces(float delta);
	public:
		Simulation();
		~Simulation();


		void ProcessSimulationFrame(float delta);
		void ResetSim();
		void ResetConstants();
		Constants* GetConstantsPtr();
		void DrawElements(glm::mat4& VP, Renderer& renderer);

		double GetPercentDeflected();
		double GetPercentBackScatter();
	};
}