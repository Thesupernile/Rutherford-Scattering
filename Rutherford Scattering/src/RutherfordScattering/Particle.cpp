#include "Particle.h"
#include <iostream>

std::vector<RutherfordScattering::Particle::objectVertex> RutherfordScattering::Particle::objectVertices;
std::vector<objectIndex> RutherfordScattering::Particle::objectIndexes;

void RutherfordScattering::Particle::generateParticleVertexes()
{
    // Plus one is for the centre and the two is for the two coordinates
    objectVertices.push_back({ 0.0f, 0.0f, 0.5f, 0.5f });

    const float anglePerVertex = (2 * PI) / (numVerticesPerObject - 1);

    for (int i = 1; i < numVerticesPerObject; i++) {
        objectVertex newVertex;

        // Add the vertex at the correct x and y pos
        newVertex.x = cos(anglePerVertex * i);
        newVertex.y = sin(anglePerVertex * i);

        // Add the texture coordinates (+ 1 then / 2 is to convert the range -1 to 1 to 0 to 1)
        newVertex.u = (cos(anglePerVertex * i) + 1) / 2;
        newVertex.v = (sin(anglePerVertex * i) + 1) / 2;

        objectVertices.push_back(newVertex);
    }
}

void RutherfordScattering::Particle::generateParticleIndexes()
{
    // 3 since there is a triangle for every vertex

    for (unsigned int i = 0; i < numVerticesPerObject-1; i++) {
        objectIndex newIndex;
        // Multiply by three since there are three numbers per index
        if (i != numVerticesPerObject - 2) {
            newIndex = { 0, i + 1, i + 2 };
        }
        // Else condition necessary for wrapping the cirle back around
        else {
            newIndex = { 0, i + 1, 1};
        }
        objectIndexes.push_back(newIndex);
    }
}

void RutherfordScattering::Particle::calculateScale()
{
    float nuclearRadius = _constants.hydrogenRadius * pow(_nucleonNumber, 1.0/3.0);

    float atomicRadius = nuclearRadius * _constants.atomicRadiusMultiplier;

    _scale = _constants.simulationScaleFactor * atomicRadius;
}

RutherfordScattering::Particle::Particle(int protonNumber, int nucleonNumber, Constants& constants)
: _protonNumber(protonNumber), _nucleonNumber(nucleonNumber), _constants(constants), DrawableObject() {
    layout.Push<float>(2);
    layout.Push<float>(2);

    calculateScale();

    SetVertexBufferData(objectVertices.data(), numVerticesPerObject * sizeof(objectVertex));
    SetIndexBufferData(ParseIndices(objectIndexes).data(), (numVerticesPerObject-1) * 3);
    SetShader(shaderFilePath);
    SetTexture(textureFilePath);
}

RutherfordScattering::Particle::Particle(const Particle& oldParticle) :
    DrawableObject(oldParticle), _protonNumber(oldParticle._protonNumber), _nucleonNumber(oldParticle._nucleonNumber), _constants(oldParticle._constants)
{
    _velocity = oldParticle._velocity;
    _isMovable = oldParticle._isMovable;

    objectIndexes = oldParticle.objectIndexes;
    objectVertices = oldParticle.objectVertices;

    SetVertexBufferData(objectVertices.data(), numVerticesPerObject * sizeof(objectVertex));
    SetIndexBufferData(ParseIndices(objectIndexes).data(), (numVerticesPerObject - 1) * 3);
    SetShader(shaderFilePath);
    SetTexture(textureFilePath);
}

RutherfordScattering::Particle::~Particle()
{

}

void RutherfordScattering::Particle::incrementFrame() {

}

bool RutherfordScattering::Particle::isMovable()
{
    return _isMovable;
}

int RutherfordScattering::Particle::getNuclearRadius()
{
    return 0;
}

int RutherfordScattering::Particle::getAtomicRadius()
{
    return 0;
}
