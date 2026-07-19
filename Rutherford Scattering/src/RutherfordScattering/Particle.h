#pragma once
#include "DrawableObject.h"
#include "Constants.h"

#include <string>
#include <memory>

namespace RutherfordScattering {

	class Simulation;

	class Particle : public DrawableObject {
	private:
		static constexpr float PI = 3.141592;

		int _protonNumber;
		int _nucleonNumber;
		float _charge;
		bool _isMovable;
		bool _isPersistent;
		int _timeToLive;
		Constants& _constants;

		static const int numVerticesPerObject = 129;
		static std::vector<objectVertex> objectVertices;
		static std::vector<objectIndex> objectIndexes;

		glm::vec3 _velocity = glm::vec3(0, 0, 0);

		void calculateScale();
		void calculateCharge();
		void determineColour();

	public:
		Particle(int protonNumber, int nucleonNumber, Constants& constants);
		Particle(const Particle& oldParticle);
		~Particle();

		static void generateParticleVertexes();
		static void generateParticleIndexes();

		void incrementFrame() override;

		bool isPersistent() { return _isPersistent; }
		void setPersistent(bool isPersist) { _isPersistent = isPersist; }
		void setIsMovable(bool newValue);
		bool isMovable();

		int getNuclearRadius();
		int getAtomicRadius();
		int getTimeToLive() { return _timeToLive; }
		void setTimeToLive(int newTTL) { _timeToLive = newTTL; }

		void setVelocity(glm::vec3 newVelocity);
		glm::vec3 getVelocity();

		float getCharge() { return _charge; }

		void processElectromagneticForces(glm::vec3 particlePosition, int particleCharge);
	};

}