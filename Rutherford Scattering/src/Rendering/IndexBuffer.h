#pragma once

struct objectIndex {
	unsigned int v1;
	unsigned int v2;
	unsigned int v3;
};

class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer();
	~IndexBuffer();

	void AddBufferData(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};