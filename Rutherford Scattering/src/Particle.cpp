#include "Particle.h"

void RutherfordScattering::Particle::generateParticleVertexes()
{
    pVertices = new objectVertex[numVerticesPerObject];

    // Plus one is for the centre and the two is for the two coordinates
    pVertices[0] = { 0.0f, 0.0f, 0.5f, 0.5f };

    const float anglePerVertex = (2 * PI) / (numVerticesPerObject - 1);

    for (int i = 1; i < numVerticesPerObject; i++) {
        // Add the vertex at the correct x and y pos
        pVertices[i].x = cos(anglePerVertex * i);
        pVertices[i].y = sin(anglePerVertex * i);

        // Add the texture coordinates (+ 1 then / 2 is to convert the range -1 to 1 to 0 to 1)
        pVertices[i].u = (cos(anglePerVertex * i) + 1) / 2;
        pVertices[i].v = (sin(anglePerVertex * i) + 1) / 2;
    }
}

void RutherfordScattering::Particle::generateParticleIndexes()
{
    // 3 since there is a triangle for every vertex
    pIndexes = new objectIndex[numVerticesPerObject-1];

    for (int i = 0; i < numVerticesPerObject-1; i++) {
        // Multiply by three since there are three numbers per index
        pIndexes[i].v1 = 0;
        pIndexes[i].v2 = i + 1;
        if (i != numVerticesPerObject - 2) {
            pIndexes[i].v3 = i + 2;
        }
        // Else condition necessary for wrapping the cirle back around
        else {
            pIndexes[i].v3 = 1;
        }
    }
}

RutherfordScattering::Particle::Particle(int protonNumber, int nucleonNumber, Constants& constants)
: protonNumber(protonNumber), nucleonNumber(nucleonNumber), constants(constants), DrawableObject() {
    layout.Push<float>(2);
    layout.Push<float>(2);

    numVerticesPerObject = 129;
    generateParticleVertexes();
    generateParticleIndexes();

    SetVertexBufferData(pVertices, numVerticesPerObject * sizeof(objectVertex));
    SetIndexBufferData(ParseIndices(pIndexes).data(), (numVerticesPerObject-1) * 3);
    SetShader(shaderFilePath);
    SetTexture(textureFilePath);
}

RutherfordScattering::Particle::~Particle()
{

}

void RutherfordScattering::Particle::incrementFrame()
{

}

void RutherfordScattering::Particle::processElectromagneticForces(glm::vec3 particlePosition, int particleCharge)
{
    
}