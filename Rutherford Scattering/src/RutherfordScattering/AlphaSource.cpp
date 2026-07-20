#include "AlphaSource.h"

void RutherfordScattering::AlphaSource::GenerateObjectVertices()
{
	// Adds the coordinates for the alpha source's vertices
	objectVertices.emplace_back(objectVertex({ 0.0, 0.0, 0.0, 0.0 }));
	objectVertices.emplace_back(objectVertex({ 0.0, 1.0, 0.0, 1.0 }));
	objectVertices.emplace_back(objectVertex({ 0.5, 0.0, 0.5, 0.0 }));
	objectVertices.emplace_back(objectVertex({ 0.5, 1.0, 0.5, 1.0 }));
	objectVertices.emplace_back(objectVertex({ 0.5, 0.3, 0.5, 0.3 }));
	objectVertices.emplace_back(objectVertex({ 0.5, 0.7, 0.5, 0.7 }));
	objectVertices.emplace_back(objectVertex({ 0.9, 0.3, 0.9, 0.3 }));
	objectVertices.emplace_back(objectVertex({ 0.9, 0.7, 0.9, 0.7 }));
}

void RutherfordScattering::AlphaSource::GenerateObjectIndicies()
{
	// Adds the indexes for the alpha source's vertices vertices
	objectIndexes.emplace_back(objectIndex({ 0, 1, 2 }));
	objectIndexes.emplace_back(objectIndex({ 1, 2, 3 }));
	objectIndexes.emplace_back(objectIndex({ 4, 5, 6 }));
	objectIndexes.emplace_back(objectIndex({ 5, 6, 7 }));
}

RutherfordScattering::AlphaSource::AlphaSource()
{
	// Default values for members are semi random
	_angle =		0;	
	_emissionRate = 1;	
	_gapWidth =		2;	
	_sourceSpread =	0.3;	
	_scale =		40;

	layout.Push<float>(2);
	layout.Push<float>(2);

	numVerticesPerObject = 4;
	GenerateObjectVertices();
	GenerateObjectIndicies();

	SetVertexBufferData(objectVertices.data(), objectVertices.size() * sizeof(objectVertex));
	SetIndexBufferData(ParseIndices(objectIndexes).data(), objectIndexes.size() * 3);
	SetShader(shaderFilePath);
	SetTexture(textureFilePath);
}

RutherfordScattering::AlphaSource::~AlphaSource()
{
}

RutherfordScattering::AlphaSource::AlphaSource(const AlphaSource& oldObject) :
	DrawableObject(oldObject)
{
	_angle = oldObject._angle;
	_emissionRate = oldObject._emissionRate;
	_gapWidth = oldObject._gapWidth;
	_sourceSpread = oldObject._sourceSpread;

	numVerticesPerObject = oldObject.numVerticesPerObject;
	objectIndexes = oldObject.objectIndexes;
	objectVertices = oldObject.objectVertices;

	SetVertexBufferData(objectVertices.data(), objectVertices.size() * sizeof(objectVertex));
	SetIndexBufferData(ParseIndices(objectIndexes).data(), objectIndexes.size() * 3);
	SetShader(shaderFilePath);
	SetTexture(textureFilePath);
}

void RutherfordScattering::AlphaSource::IncrementFrame()
{

}

void RutherfordScattering::AlphaSource::SetEmissionRate(int newEmissionRate)
{
	_emissionRate = newEmissionRate;
}

int RutherfordScattering::AlphaSource::GetEmissionRate()
{
	return _emissionRate;
}

void RutherfordScattering::AlphaSource::SetAngle(float newAngle)
{
	_angle = newAngle;
}

int RutherfordScattering::AlphaSource::GetAngle()
{
	return _angle;
}
