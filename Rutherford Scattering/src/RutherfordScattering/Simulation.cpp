#include "Simulation.h"

void RutherfordScattering::Simulation::CreateFoil()
{
	for (unsigned int i = 0; i < constants.foilWidth; i++) {
		for (unsigned int j = 0; j < constants.foilLength; j++) {
			_particles.emplace_back(Particle(40, 150, constants));
			_particles[i*constants.foilLength + j].SetPos(10 * i + 600, 10 * j, 0);
		}
	}
}

void RutherfordScattering::Simulation::CreateAlphaSources()
{
	_alphaSources.emplace_back(AlphaSource());
	_alphaSources[0].SetPos(0, 350, 0);
}

void RutherfordScattering::Simulation::ProcessAlphaEmissions()
{

}

void RutherfordScattering::Simulation::ProcessParticleMovement()
{
	for (auto& particle : _particles) {
		particle.incrementFrame();
	}
}

void RutherfordScattering::Simulation::ProcessElectrostaticForces()
{

}

RutherfordScattering::Simulation::Simulation()
{
	constants.permitivityOfFreeSpace = 8.12e-12;
	constants.hydrogenRadius = 1.2e-15;
	constants.nucleonMass = 1.67e-27;
	constants.atomicRadiusMultiplier = 1e5;

	Particle::generateParticleVertexes();
	Particle::generateParticleIndexes();

	CreateFoil();
	CreateAlphaSources();

	// Temp Test Code
	_particles.emplace_back(2, 4, constants);
	_particles[_particles.size()-1].SetPos(0, 350, 0);
	_particles[_particles.size() - 1].setVelocity(glm::vec3({ 1, 0, 0 }));
}

RutherfordScattering::Simulation::~Simulation()
{

}

void RutherfordScattering::Simulation::ProcessSimulationFrame()
{
	ProcessAlphaEmissions();
	ProcessParticleMovement();
	ProcessElectrostaticForces();
}

void RutherfordScattering::Simulation::SetNewConstants(Constants newConstants)
{
	constants = newConstants;
	CreateFoil();
	CreateAlphaSources();
}

void RutherfordScattering::Simulation::DrawElements(glm::mat4& VP, Renderer& renderer)
{
	for (auto& particle : _particles) {
		particle.Draw(VP, renderer);
	}
	for (auto& alphasource : _alphaSources) {
		alphasource.Draw(VP, renderer);
	}
}
