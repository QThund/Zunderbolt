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

#include "ZMemory/AllocationOperators.h"


void* operator new(const size_t uSize, const z::Alignment& alignment)
{
    // In C++ there's no way of providing a data type or class whose size is zero, the size of an empty struct
    // or class will be 1 byte, in order to avoid two objects to be addressed at the same memory address.
    // In C, a struct cannot be empty because the syntax forbids it. However, there may be compilers (such as gcc)
    // that allow this feature in C as an extension, having zero as size, so the following check becomes necessary.
    //
    // More info in:
    // http://isocpp.org/wiki/faq/classes-and-objects#sizeof-empty
    // http://gcc.gnu.org/onlinedocs/gcc/Empty-Structures.html
    Z_ASSERT_ERROR (uSize > 0, "The size of the memory block to reserve cannot be zero");

    // If failed, a null pointer is returned from the allocation function.
    void* p = aligned_alloc_z(uSize, alignment);
    Z_ASSERT_ERROR (null_z != p, "It was not possible to reserve memory with such alignment");

    // If passed, the memory block is aligned according to its corresponding alignment value.
    Z_ASSERT_ERROR ( 0 == ( (rcast_z(p, z::puint_z)) & (alignment - 1) ), "An error occurred, the obtained memory address is not aligned" );

    return p;
}

void* operator new[](const size_t uSize, const z::Alignment& alignment)
{
    // In C++ there's no way of providing a data type or class whose size is zero, the size of an empty struct
    // or class will be 1 byte, in order to avoid two objects to be addressed at the same memory address.
    // In C, a struct cannot be empty because the syntax forbids it. However, there may be compilers (such as gcc)
    // that allow this feature in C as an extension, having zero as size, so the following check becomes necessary.
    //
    // More info in:
    // http://isocpp.org/wiki/faq/classes-and-objects#sizeof-empty
    // http://gcc.gnu.org/onlinedocs/gcc/Empty-Structures.html
    Z_ASSERT_ERROR (uSize > 0, "The size of the memory block to reserve cannot be zero");

    // If failed, a null pointer is returned from the allocation function.
    void* p = aligned_alloc_z(uSize, alignment);
    Z_ASSERT_ERROR (null_z != p, "It was not possible to reserve memory with such alignment");

    // If passed, the memory block is aligned according to its regarding alignment value.
    Z_ASSERT_ERROR ( 0 == ( (rcast_z(p, z::puint_z)) & (alignment - 1) ), "An error occurred, the obtained memory address is not aligned" );

    return p;
}


void operator delete(void* pMemoryBlock, const z::Alignment& alignment)
{
    // If failed, the memory block was not aligned according to its corresponding alignment value.
    Z_ASSERT_ERROR ( 0 == ( (rcast_z(pMemoryBlock, z::puint_z)) & (alignment - 1) ), "The memory address must be aligned to call this operator" );

    aligned_free_z(pMemoryBlock);
}

void operator delete[](void* pMemoryBlock, const z::Alignment& alignment)
{
    // If failed, the memory block was not aligned according to its corresponding alignment value.
    Z_ASSERT_ERROR ( 0 == ( (rcast_z(pMemoryBlock, z::puint_z)) & (alignment - 1) ), "The memory address must be aligned to call this operator" );

    aligned_free_z(pMemoryBlock);
}

#ifdef Z_PREPROCESSOR_EXPORTLIB_COMMON

void* operator new(const size_t uSize) throw(std::bad_alloc)
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != z::null_z, "Fatal error: No memory could be allocated");

    return p;
}

void* operator new(const size_t uSize, const std::nothrow_t& nothrow_value) throw()
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != z::null_z, "Fatal error: No memory could be allocated");

    return p;
}

void* operator new[](const size_t uSize) throw(std::bad_alloc)
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != z::null_z, "Fatal error: No memory could be allocated");

    return p;
}

void* operator new[](const size_t uSize, const std::nothrow_t& nothrow_value) throw()
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != z::null_z, "Fatal error: No memory could be allocated");

    return p;
}

void operator delete(void* pMemoryBlock) throw()
{
    free(pMemoryBlock);
}

void operator delete(void* pMemoryBlock, const std::nothrow_t& nothrow_constant) throw()
{
    free(pMemoryBlock);
}

void operator delete[](void* pMemoryBlock) throw()
{
    free(pMemoryBlock);
}

void operator delete[](void* pMemoryBlock, const std::nothrow_t& nothrow_constant) throw()
{
    free(pMemoryBlock);
}

#endif
