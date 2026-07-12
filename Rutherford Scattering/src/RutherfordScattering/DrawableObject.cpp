#include "DrawableObject.h"

RutherfordScattering::DrawableObject::DrawableObject()
{
}

void RutherfordScattering::DrawableObject::SetVertexBufferData(const void* data, unsigned int size) {
	vb.AddBufferData(data, size);
	va.AddBuffer(vb, layout);
}

void RutherfordScattering::DrawableObject::SetIndexBufferData(unsigned int* data, unsigned int count) {
	ib.AddBufferData(data, count);
}

void RutherfordScattering::DrawableObject::SetShader(std::string path) {
	shader.SetShaderProgram(path);
}

void RutherfordScattering::DrawableObject::SetTexture(std::string path) {
	texture.SetTexture(path);
}

RutherfordScattering::DrawableObject::~DrawableObject()
{

}

RutherfordScattering::DrawableObject::DrawableObject(const DrawableObject& oldObject)
{
	shaderFilePath = oldObject.shaderFilePath;
	textureFilePath = oldObject.textureFilePath;

	layout = oldObject.layout;

	_scale = oldObject._scale;
	_position = oldObject._position;
}

std::vector<unsigned int> RutherfordScattering::DrawableObject::ParseIndices(std::vector<objectIndex> data) {
	std::vector<unsigned int> parsedData;

	for (int i = 0; i < data.size(); i++) {
		parsedData.push_back(data[i].v1);
		parsedData.push_back(data[i].v2);
		parsedData.push_back(data[i].v3);
	}

	return parsedData;
}

void RutherfordScattering::DrawableObject::SetPos(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void RutherfordScattering::DrawableObject::Draw(glm::mat4& VPMatrix, Renderer& renderer)
{
	va.Bind();
	shader.Bind();
	texture.Bind();
	
	glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3({ 0,0,1 })); // 0, 0, 1 as axis of rotation as rotating about the z axis (hence a normal rotation in 2d)
	modelMatrix = glm::translate(modelMatrix, _position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(_scale));
	glm::mat4 MVP = VPMatrix * modelMatrix;

	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("u_Colour", 1.0f, 1.0f, 0.0f, 1.0f);
	shader.SetUniformMat4f("u_MVP", MVP);

	renderer.Draw(va, ib, shader);
}
