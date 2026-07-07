#include "Simulation.h"

void RutherfordScattering::Simulation::CreateFoil()
{
	_particles.emplace_back(Particle(40, 50, constants));
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
	CreateFoil();
}

RutherfordScattering::Simulation::~Simulation()
{

}

void RutherfordScattering::Simulation::ProcessSimulationFrame()
{

}

void RutherfordScattering::Simulation::SetNewConstants(Constants newConstants)
{
	constants = newConstants;
	CreateFoil();
}

void RutherfordScattering::Simulation::DrawElements(glm::mat4& VP, Renderer& renderer)
{
	for (auto& particle : _particles) {
		particle.Draw(VP, renderer);
	}
}
