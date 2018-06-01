//-------------------------------------------------------------------------------//
//                             ZUNDERBOLT : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Zunderbolt.                                              //
// Zunderbolt is free software: you can redistribute it and/or modify            //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Zunderbolt is distributed in the hope that it will be useful,                 //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Zunderbolt. If not, see <http://www.gnu.org/licenses/>.            //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Zunderbolt in your project but we would appreciate         //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "ZMemory/LinearAllocator.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/AllocationOperators.h"
#include <cstring>

namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

LinearAllocator::LinearAllocator(const puint_z uSize, const Alignment &alignment) : 
                                                                 m_uSize(uSize),
                                                                 m_bUsesExternalBuffer(false),
                                                                 m_uAlignment(alignment)
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");

    m_pBase = ::operator new(uSize, alignment);
    m_pTop = m_pBase;
}

LinearAllocator::LinearAllocator(const puint_z uSize, void* pBuffer) : m_pBase(pBuffer),
                                                                       m_pTop(pBuffer),
                                                                       m_uSize(uSize),
                                                                       m_bUsesExternalBuffer(true),
                                                                       m_uAlignment(1U)
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");
    Z_ASSERT_ERROR(pBuffer != null_z, "The pointer to the external buffer cannot be null.");
}
    
LinearAllocator::LinearAllocator(const puint_z uSize, void* pBuffer, const Alignment &alignment) : 
                                                                                m_pBase(pBuffer),
                                                                                m_pTop(pBuffer),
                                                                                m_uSize(uSize),
                                                                                m_bUsesExternalBuffer(true),
                                                                                m_uAlignment(alignment)
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the buffer cannot be zero.");
    Z_ASSERT_ERROR(pBuffer != null_z, "The pointer to the external buffer cannot be null.");

    puint_z uAdjustment = m_uAlignment - ((puint_z)m_pBase & (m_uAlignment - 1U));

    // Changes the base pointer to the first memory address that is aligned as intended
    if(uAdjustment != m_uAlignment)
    {
        m_pBase = (void*)((puint_z)m_pBase + uAdjustment);
        m_pTop = m_pBase;
        m_uSize -= uAdjustment; // Some free space is lost
    }
}
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

LinearAllocator::~LinearAllocator()
{
    if(!m_bUsesExternalBuffer)
        ::operator delete(m_pBase, Alignment(m_uAlignment));
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void* LinearAllocator::Allocate(const puint_z uSize)
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");
    Z_ASSERT_WARNING(this->CanAllocate(uSize), "The size of the memory block to be allocated does not fit in the available free space.");

    void* pAllocatedMemory = null_z;
    
    if(this->CanAllocate(uSize))
    {
        pAllocatedMemory = m_pTop;
        m_pTop = (void*)((puint_z)m_pTop + uSize);
    }

    return pAllocatedMemory;
}

void* LinearAllocator::Allocate(const puint_z uSize, const Alignment &alignment)
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");
    Z_ASSERT_WARNING(this->CanAllocate(uSize, alignment), "The size of the memory block to be allocated (plus the alignment adjustment) does not fit in the available free space.");

    void* pAllocatedMemory = null_z;

    if(this->CanAllocate(uSize, alignment))
    {
        puint_z uAdjustment = alignment - ((puint_z)m_pTop & (alignment - 1U));

        if(uAdjustment == alignment)
            uAdjustment = 0;

        pAllocatedMemory = (void*)((puint_z)m_pTop + uAdjustment);
        m_pTop = (void*)((puint_z)m_pTop + uSize + uAdjustment);
    }

    return pAllocatedMemory;
}

void LinearAllocator::Clear()
{
    m_pTop = m_pBase;
}

void LinearAllocator::CopyTo(LinearAllocator &destination) const
{
    Z_ASSERT_ERROR(destination.GetSize() >= this->GetAllocatedBytes(), "The input allocator's size must be greater than or equal to the size of the allocated bytes in the resident allocator.");
    Z_ASSERT_WARNING(destination.m_uAlignment == m_uAlignment, "The alignment of the input allocator is different from the resident allocator's.");

    const puint_z BYTES_TO_COPY = this->GetAllocatedBytes();

    memcpy(destination.m_pBase, m_pBase, BYTES_TO_COPY);

    destination.m_pTop = (void*)((puint_z)destination.m_pBase + BYTES_TO_COPY);
}

void LinearAllocator::Reallocate(const puint_z uNewSize)
{
    Z_ASSERT_ERROR(!m_bUsesExternalBuffer, "This allocator uses an external buffer so internal reallocation is not possible");
    Z_ASSERT_WARNING(uNewSize > m_uSize, "The new size must be greater than the current size");

    if(uNewSize > m_uSize)
    {
        const puint_z BYTES_TO_COPY = this->GetAllocatedBytes();

        void* pNewBuffer = ::operator new(uNewSize, Alignment(m_uAlignment));
        memcpy(pNewBuffer, m_pBase, BYTES_TO_COPY);
        ::operator delete(m_pBase, Alignment(m_uAlignment));
        m_pBase = pNewBuffer;
        m_pTop = (void*)((puint_z)m_pBase + BYTES_TO_COPY);
        m_uSize = uNewSize;
    }
}

void LinearAllocator::Reallocate(const puint_z uNewSize, void* pNewLocation)
{
    Z_ASSERT_ERROR(m_bUsesExternalBuffer, "This allocator uses an internal buffer so external reallocation is not possible");
    Z_ASSERT_ERROR(pNewLocation != null_z, "The pointer to the new buffer cannot be null");
    Z_ASSERT_WARNING(uNewSize > m_uSize, "The new size must be greater than the current size");

    if(uNewSize > m_uSize)
    {
        puint_z uAdjustment = m_uAlignment - ((puint_z)pNewLocation & (m_uAlignment - 1U));

        if(uAdjustment == m_uAlignment)
            uAdjustment = 0;

        const puint_z ADJUSTED_SIZE = uNewSize - uAdjustment;
        Z_ASSERT_WARNING(ADJUSTED_SIZE > m_uSize, "Due to the alignment adjustment, there is not enough space in the new buffer to allocate the data to be moved");

        if(ADJUSTED_SIZE > m_uSize)
        {
            const puint_z BYTES_TO_COPY = this->GetAllocatedBytes();
            void* pAdjustedLocation = (void*)((puint_z)pNewLocation + uAdjustment);
            memcpy(pAdjustedLocation, m_pBase, BYTES_TO_COPY);

            // Changes the base pointer to the first memory address that is aligned as intended
            m_pBase = pAdjustedLocation;
            m_pTop = (void*)((puint_z)m_pBase + BYTES_TO_COPY);
            m_uSize = ADJUSTED_SIZE; // Some free space may be lost
        }
    }
}

bool LinearAllocator::CanAllocate(const puint_z uSize) const
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    return m_uSize - this->GetAllocatedBytes() >= uSize;
}

bool LinearAllocator::CanAllocate(const puint_z uSize, const Alignment &alignment) const
{
    Z_ASSERT_ERROR(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    puint_z uAdjustment = alignment - ((puint_z)m_pTop & (alignment - 1U));

    if(uAdjustment == alignment)
        uAdjustment = 0;

    return m_uSize - this->GetAllocatedBytes() >= uSize + uAdjustment;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

puint_z LinearAllocator::GetSize() const
{
    return m_uSize;
}

puint_z LinearAllocator::GetAllocatedBytes() const
{
    return (puint_z)m_pTop - (puint_z)m_pBase;
}

void* LinearAllocator::GetPointer() const
{
    return m_pBase;
}


} // namespace z
