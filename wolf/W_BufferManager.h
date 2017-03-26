//-----------------------------------------------------------------------------
// File:			W_BufferManager.h
// Original Author:	Gordon Wood
//
// Class to manage Buffers. This isn't strictly needed in our use-cases as all
// it does is delegate through to the buffer classes themselves. However, it's 
// provided as an intermediate step. In a future expansion, you may want to
// store a copy of all buffers created so you can later run through them and
// reload them if, say, your context is lost. This is left as an exercise.
//-----------------------------------------------------------------------------
#ifndef W_BUFFER_MANAGER_H
#define W_BUFFER_MANAGER_H

#include "W_Types.h"
#include "W_VertexBuffer.h"
#include "W_IndexBuffer.h"
#include <string>
#include <map>

namespace wolf
{
class BufferManager
{
	public:
		//-------------------------------------------------------------------------
		// PUBLIC INTERFACE
		//-------------------------------------------------------------------------
		static BufferManager* Inst();
		VertexBuffer* CreateVertexBuffer(unsigned int p_uiLength);
		VertexBuffer* CreateVertexBuffer(const void* p_pData, unsigned int p_uiLength);
		IndexBuffer* CreateIndexBuffer(unsigned int p_uiNumIndices);

		void DestroyBuffer(Buffer* p_pBuf);
		virtual ~BufferManager();
		//-------------------------------------------------------------------------
	protected:
		BufferManager();
		BufferManager(const BufferManager& bm);
		BufferManager& operator=(const BufferManager& bm);

	private:
		static BufferManager* m_inst;
};

}

#endif




