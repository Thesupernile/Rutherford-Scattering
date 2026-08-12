#include "Simulation.h"

void RutherfordScattering::Simulation::CreateFoil()
{
	for (unsigned int i = 0; i < constants.foilWidth; i++) {
		for (unsigned int j = 0; j < constants.foilLength; j++) {
			_particles.emplace_back(Particle(40, 150, constants));
			_particles.back().SetPos(glm::vec3({10 * i + 600, 10 * j, 0}));
		}
	}
}

void RutherfordScattering::Simulation::CreateAlphaSources()
{
	_alphaSources.emplace_back(AlphaSource());
	_alphaSources[0].SetPos(glm::vec3({ 15, 350, 0 }));
}

void RutherfordScattering::Simulation::ProcessAlphaEmissions()
{
	const int numProtons = constants.numProtonsPerAlpha;
	const int numNucleons = constants.numNeutronsPerAlpha + numProtons;
	const int alphaParticleSpeed = constants.alphaParticleInitialSpeed;

	for (auto& alphasource : _alphaSources) {
		alphasource.SetPos(glm::vec3({ constants.alphaSourcePos.x, constants.alphaSourcePos.y, 0 }));
		// Angles are converted from degrees to radians for better usability
		alphasource.SetAngle(constants.alphaSourceAngle/360 * (2 * PI));
		alphasource.SetSourceSpread(constants.alphaSourceSpread / 360 * (2 * PI));
		
		alphasource.SetEmissionRate(constants.alphaSourceEmissionRate);

		float numParticlesToGenerate;
		float fractionalnumParticlesToGenerate = std::modf(alphasource.GetEmissionRate(), &numParticlesToGenerate);

		int inverse = 1 / fractionalnumParticlesToGenerate;
		// Deal with fractional component as a probablility (probablility rounded)
		if ((rand() % inverse) == 0) {
			numParticlesToGenerate++;
		}

		for (int i = 0; i < numParticlesToGenerate; i++) {

			unsigned int endOfList = _particles.size();
			_particles.emplace_back(numProtons, numNucleons, constants);

			// Gets a random value between +- alphaSourceSpread to 4 decimal places (in radians)
			float offsetAngle = 0;
			if (alphasource.GetSourceSpread() != 0) {
				int preAdjustedOffsetAngle = rand() % (int)(10000 * alphasource.GetSourceSpread() * 2);
				offsetAngle = preAdjustedOffsetAngle / 10000.0 - alphasource.GetSourceSpread();
			}
			float emissionAngle = alphasource.GetAngle() + offsetAngle;

			float xVelocity = cos(emissionAngle) * alphaParticleSpeed;
			float yVelocity = sin(emissionAngle) * alphaParticleSpeed;

			// Offset to position the spawned alpha particle at the front of the source
			float offsetX = alphasource.GetScale() / 2 + alphasource.GetScale() / 2 * cos(alphasource.GetAngle());
			float offsetY = alphasource.GetScale() / 2 + alphasource.GetScale() / 2 * sin(alphasource.GetAngle());

			_particles.back().SetPos(alphasource.GetPos() + glm::vec3({offsetX, offsetY, 0}));
			_particles.back().SetVelocity(glm::vec3({ xVelocity, yVelocity, 0 }));
			_particles.back().SetTimeToLive(constants.defaultParticleTTL);
			_particles.back().SetPersistent(false);
		}
	}
}

void RutherfordScattering::Simulation::ProcessParticleMovement()
{
	std::vector<unsigned int> particlesToCull;
	unsigned int i = 0;

	for (auto& particle : _particles) {
		if (!particle.IsPersistent() && particle.GetTimeToLive() <= 0) {
			particlesToCull.push_back(i);
		}
		else {
			particle.IncrementFrame();
		}
		i++;
	}

	// TODO Refactor to avoid repetitive advancing through all the static particles
	for (unsigned int index : particlesToCull) {
		std::list<Particle>::iterator iter = _particles.begin();
		std::advance(iter, index);
		_particles.erase(iter);
	}
}

void RutherfordScattering::Simulation::ProcessParticleForcesOneThread() {
	while (currentParticle < _particles.size()) {
		std::list<Particle>::iterator particle1 = particleIterator;
		std::advance(particleIterator, 1);
		currentParticle++;

		if (!particle1->IsPersistent()) {
			for (auto& particle2 : _particles) {
				// Persistent particles make up the foil (other particles excluded for performance reasons)
				if (particle2.IsPersistent()) {
					particle1->ProcessElectromagneticForces(particle2.GetPos(), particle2.GetCharge());
				}
			}
		}
	}
}

void RutherfordScattering::Simulation::ProcessElectrostaticForces()
{
	std::vector<std::thread> threads;
	currentParticle = 0;
	particleIterator = _particles.begin();

	for (int i = 0; i < constants.maxNumThreads; i++) {
		if (currentParticle < _particles.size()) {
			threads.push_back(std::thread(&RutherfordScattering::Simulation::ProcessParticleForcesOneThread, this));
			currentParticle++;
		}
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

RutherfordScattering::Simulation::Simulation()
{
	constants.permitivityOfFreeSpace = 8.12e-12;
	constants.hydrogenRadius = 1.2e-15;
	constants.nucleonMass = 1.67e-27;
	constants.atomicRadiusMultiplier = 1e5;

	CreateFoil();
	CreateAlphaSources();
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

RutherfordScattering::Constants* RutherfordScattering::Simulation::GetConstantsPtr()
{
	return &constants;
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
