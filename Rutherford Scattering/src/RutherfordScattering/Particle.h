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

		void CalculateScale();
		void CalculateCharge();
		void DetermineColour();

	public:
		Particle(int protonNumber, int nucleonNumber, Constants& constants);
		Particle(const Particle& oldParticle);
		~Particle();

		static void GenerateParticleVertexes();
		static void GenerateParticleIndexes();

		void IncrementFrame() override;

		bool IsPersistent() { return _isPersistent; }
		void SetPersistent(bool isPersist) { _isPersistent = isPersist; }
		void SetIsMovable(bool newValue);
		bool IsMovable();

		int GetNuclearRadius();
		int GetAtomicRadius();
		int GetTimeToLive() { return _timeToLive; }
		void SetTimeToLive(int newTTL) { _timeToLive = newTTL; }

		void SetVelocity(glm::vec3 newVelocity);
		glm::vec3 GetVelocity();

		float GetCharge() { return _charge; }

		void ProcessElectromagneticForces(glm::vec3 relativeParticlePosition, float particleCharge, float secondParticleNuclearRadius);
	};

}