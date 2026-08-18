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
	objectVertices.emplace_back(objectVertex({ 1.0, 0.3, 1.0, 0.3 }));
	objectVertices.emplace_back(objectVertex({ 1.0, 0.7, 1.0, 0.7 }));
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
	_rotation =		PI;	
	_emissionRate = 1;	
	_gapWidth =		2;	
	_sourceSpread =	0.1;	
	_scale =		40;

	layout.Push<float>(2);
	layout.Push<float>(2);

	numVerticesPerObject = 4;
	GenerateObjectVertices();
	GenerateObjectIndicies();

	SetVertexBufferData(objectVertices.data(), objectVertices.size() * sizeof(objectVertex), vb, va, layout);
	SetIndexBufferData(ParseIndices(objectIndexes).data(), objectIndexes.size() * 3, ib);
	SetShader(shaderFilePath, shader);
	SetTexture(textureFilePath, texture);
}

RutherfordScattering::AlphaSource::~AlphaSource()
{
}

RutherfordScattering::AlphaSource::AlphaSource(const AlphaSource& oldObject) :
	DrawableObject(oldObject)
{
	_emissionRate = oldObject._emissionRate;
	_gapWidth = oldObject._gapWidth;
	_sourceSpread = oldObject._sourceSpread;

	numVerticesPerObject = oldObject.numVerticesPerObject;
	objectIndexes = oldObject.objectIndexes;
	objectVertices = oldObject.objectVertices;

	shaderFilePath = oldObject.shaderFilePath;

	layout.Push<float>(2);
	layout.Push<float>(2);

	SetVertexBufferData(objectVertices.data(), objectVertices.size() * sizeof(objectVertex), vb, va, layout);
	SetIndexBufferData(ParseIndices(objectIndexes).data(), objectIndexes.size() * 3, ib);
	SetShader(shaderFilePath, shader);
	SetTexture(textureFilePath, texture);
}

void RutherfordScattering::AlphaSource::IncrementFrame(float delta)
{

}

void RutherfordScattering::AlphaSource::SetEmissionRate(float newEmissionRate)
{
	_emissionRate = newEmissionRate;
}

float RutherfordScattering::AlphaSource::GetEmissionRate()
{
	return _emissionRate;
}

void RutherfordScattering::AlphaSource::SetAngle(float newAngle)
{
	_rotation = newAngle;
}

float RutherfordScattering::AlphaSource::GetAngle()
{
	return _rotation;
}

void RutherfordScattering::AlphaSource::Draw(glm::mat4& VPMatrix, Renderer& renderer)
{
	DrawObject(VPMatrix, renderer, va, ib, shader);
}
