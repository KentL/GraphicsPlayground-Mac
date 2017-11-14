//-----------------------------------------------------------------------------
// File:			W_BufferManager.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "W_BufferManager.h"

namespace wolf
{
	BufferManager* BufferManager::m_inst(0);

	BufferManager* BufferManager::Inst()
	{
		if (!m_inst)
			m_inst = new BufferManager();

		return m_inst;
	}
	BufferManager::BufferManager() {}
	BufferManager::~BufferManager()
	{
		m_inst = 0;
	}
	//----------------------------------------------------------
	// Creates a new Vertex Buffer
	//----------------------------------------------------------
	VertexBuffer* BufferManager::CreateVertexBuffer(unsigned int p_uiLength)
	{
		return new VertexBuffer(p_uiLength);
	}

	//----------------------------------------------------------
	// Creates a new Vertex Buffer
	//----------------------------------------------------------
	VertexBuffer* BufferManager::CreateVertexBuffer(const void* p_pData, unsigned int p_uiLength)
	{
		return new VertexBuffer(p_pData,p_uiLength);
	}

	//----------------------------------------------------------
	// Creates a new Index Buffer
	//----------------------------------------------------------
	IndexBuffer* BufferManager::CreateIndexBuffer(unsigned int p_uiNumIndices)
	{
		return new IndexBuffer(p_uiNumIndices);
	}

	//----------------------------------------------------------
	// Destroys a buffer. 
	//----------------------------------------------------------
	void BufferManager::DestroyBuffer(Buffer* p_pBuf)
	{
		delete p_pBuf;
	}

}