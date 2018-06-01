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

#ifndef __ALLOCATIONOPERATORS__
#define __ALLOCATIONOPERATORS__

#include <new>
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/CommonModuleDefinitions.h"
#include "ZCommon/Alignment.h"
#include "ZCommon/Assertions.h"


#ifdef Z_COMPILER_MSVC
    #pragma warning(disable:4290) // This disables the warning C4290 produced by throw exception specification
    #pragma warning(disable:4297) // This disables the warning C4297 produced by throw exception specification
#endif

#if (defined(Z_OS_WINDOWS) || defined(Z_OS_LINUX)) && defined(Z_COMPILER_GCC)
    #include "malloc.h" // __mingw_aligned_malloc, __mingw_aligned_free
                        //
                        // [REVIEW]: __mingw_aligned_alloc and __mingw_aligned_free may be unsafe, and break the code
                        //           after time; there must be replaced by two stable and standard functions compatible
                        //           as well with MinGW.
    #include <stdlib.h>
#endif

/// <summary>
/// Aligned deallocation wrapper function, for using the allocation function provided for operative system and compiler.
/// </summary>
/// <remarks>
/// The behaviour of this function may vary depending on operative system and compiler if data alignment value, being a power of two, is either a power of sizeof(void*) as well or not:<br/>
/// <br/><br/>
/// <br/><B>MSVC:</B> It's not necessary to be a power of sizeof(void*), but to be a power of two is still mandatory.<br/>
/// <br/><B>MinGW, GCC:</B> If data alignment value is not a power of sizeof(void*) as well, the function will fix this issue automatically,
/// setting the alignment to sizeof(void*) if the entry one is lesser than it.<br/>
/// </remarks>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
/// <returns>
/// An aligned memory block of the specified type.
/// </returns>
inline void* aligned_alloc_z (const z::puint_z uSize, const z::Alignment& alignment)
{
    void* pMemoryBlock = null_z;

#ifdef Z_OS_WINDOWS
    #ifdef Z_COMPILER_MSVC
        pMemoryBlock = _aligned_malloc(uSize, alignment);
    #elif  Z_COMPILER_GCC
        // __mingw_alligned_alloc will internally set the alignment to sizeof(void*) if the entry one is lesser than it.
        //
        // [REVIEW]: __mingw_aligned_alloc may be unsafe, and break the code after time;
        //           there must be replaced with two stable and standard functions compatible
        //           as well with MinGW.
        pMemoryBlock = __mingw_aligned_malloc(uSize, alignment);
    #endif
#elif  defined (Z_OS_LINUX)
    #ifdef Z_COMPILER_GCC
        // __posix_memalign will return an error message and the allocation operation will be cancelled if the alignment value is not a power of sizeof(void*),
        // so if the entry one is lesser than it, it must be set to sizeof(void*)
        Alignment algAux( (alignment < (sizeof(void*))) ? sizeof(void*) : alignment );

        // posix_memalign won't alter the pointer value if something goes wrong,
        // so the pointer will remain to a null value.
        posix_memalign(&pMemoryBlock, algAux, uSize);
    #endif
#elif  defined (Z_OS_MAC)
    #ifdef Z_COMPILER_GCC
        // __posix_memalign will return an error message and the allocation operation will be cancelled if the alignment value is not a power of sizeof(void*),
        // so if the entry one is lesser than it, it must be set to sizeof(void*)
        Alignment algAux( (alignment < (sizeof(void*))) ? sizeof(void*) : alignment );

        // posix_memalign won't alter the pointer value if something goes wrong,
        // so the pointer will remain to a null value.
        posix_memalign(&pMemoryBlock, algAux, uSize);
    #endif
#endif

    return pMemoryBlock;
}

/// <summary>
/// Aligned deallocation wrapper function for using the deallocation function provided for operative system and compiler.
/// </summary>
/// <remarks>
/// The memory block has to be allocated using the corresponding allocation wrapper function, or undefined bahaviour (such as heap corruption assertion) may occur.
/// </remarks>
/// <param name="pMemoryBlock">[IN] Pointer to the aligned memory block to be deallocated.</param>
#ifdef Z_OS_WINDOWS
    #ifdef Z_COMPILER_MSVC
        #define aligned_free_z(pMemoryBlock)                    _aligned_free(pMemoryBlock)
    #elif Z_COMPILER_GCC
        // [REVIEW]: __mingw_aligned_alloc and __mingw_aligned_free may be unsafe, and break the code
        //           after time; there must be replaced with two stable and standard functions compatible
        //           as well with MinGW.
        #define aligned_free_z(pMemoryBlock)                    __mingw_aligned_free(pMemoryBlock)
    #endif
#elif defined(Z_OS_LINUX)
    #ifdef Z_COMPILER_GCC
        #define aligned_free_z(pMemoryBlock)                    free(pMemoryBlock)
    #endif
#elif defined(Z_OS_MAC)
    #ifdef Z_COMPILER_GCC
        #define aligned_free_z(pMemoryBlock)                    free(pMemoryBlock)
    #endif
#endif

/// <summary>
/// Allocates a memory block. Overrides the global new operator provided by the CRT libraries.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated. It must be greater than zero.</param>
/// <returns>
/// A memory block of the specified size.
/// </returns>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void* operator new (const size_t uSize) throw(std::bad_alloc)
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != null_z, "Fatal error: No memory could be allocated");

    return p;
}
#else
;
#endif

/// <summary>
/// Allocates a memory block. Overrides the global new operator provided by the CRT libraries.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated. It must be greater than zero.</param>
/// <param name="nothrow_value">[IN] Parameter used to specify that no exceptions should be thrown.</param>
/// <returns>
/// A memory block of the specified size.
/// </returns>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void* operator new (const size_t uSize, const std::nothrow_t& nothrow_value) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != null_z, "Fatal error: No memory could be allocated");

    return p;
}
#else
;
#endif

/// <summary>
/// Allocates a memory block. Overrides the global new array operator provided by the CRT libraries.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated. It must be greater than zero.</param>
/// <returns>
/// A memory block of the specified size.
/// </returns>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void* operator new[] (const size_t uSize) throw(std::bad_alloc)
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != null_z, "Fatal error: No memory could be allocated");

    return p;
}
#else
;
#endif

/// <summary>
/// Allocates a memory block. Overrides the global new array operator provided by the CRT libraries.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated. It must be greater than zero.</param>
/// <param name="nothrow_value">[IN] Parameter used to specify that no exceptions should be thrown.</param>
/// <returns>
/// A memory block of the specified size.
/// </returns>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void* operator new[] (const size_t uSize, const std::nothrow_t& nothrow_value) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    Z_ASSERT_ERROR(uSize != 0, "The size of the block to allocate must be greater than zero");

    void* p = malloc(uSize);

    Z_ASSERT_ERROR(p != null_z, "Fatal error: No memory could be allocated");

    return p;
}
#else
;
#endif

/// <summary>
/// Frees a memory block. Overrides the delete operator provided by the CRT libraries.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the memory block to be deallocated.</param>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void operator delete (void* pMemoryBlock) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    free(pMemoryBlock);
}
#else
;
#endif

/// <summary>
/// Frees a memory block. Overrides the delete operator provided by the CRT libraries.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the memory block to be deallocated.</param>
/// <param name="nothrow_constant">[IN] Parameter used to specify that no exceptions should be thrown.</param>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void operator delete (void* pMemoryBlock, const std::nothrow_t& nothrow_constant) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    free(pMemoryBlock);
}
#else
;
#endif

/// <summary>
/// Frees a memory block. Overrides the delete array operator provided by the CRT libraries.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the memory block to be deallocated.</param>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void operator delete[] (void* pMemoryBlock) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    free(pMemoryBlock);
}
#else
;
#endif

/// <summary>
/// Frees a memory block. Overrides the delete array operator provided by the CRT libraries.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the memory block to be deallocated.</param>
/// <param name="nothrow_constant">[IN] Parameter used to specify that no exceptions should be thrown.</param>
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
inline
#endif
void operator delete[] (void* pMemoryBlock, const std::nothrow_t& nothrow_constant) throw()
#ifndef Z_PREPROCESSOR_EXPORTLIB_COMMON
{
    free(pMemoryBlock);
}
#else
;
#endif

/// <summary>
/// Overload for new operator to get dynamic allocation of aligned memory blocks.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two). Please refer to the documentation of <B>alignment_alloq_z</B> for further information about the specifications of the data alignment value.</param>
/// <returns>
/// An aligned memory block of the specified size.
/// </returns>
Z_LAYER_COMMON_SYMBOLS void* operator new (const size_t uSize, const z::Alignment& alignment);

/// <summary>
/// Overload for new[] operator to get dynamic allocation of aligned memory blocks.
/// </summary>
/// <param name="uSize">[IN] Size (in bytes) of the whole memory block to be allocated (in C++, this value will always at least 1).</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two). Please refer to the documentation of <B>alignment_alloq_z</B> for further information about the specifications of the data alignment value.</param>
/// <returns>
/// An aligned memory block of the specified size.
/// </returns>
Z_LAYER_COMMON_SYMBOLS void* operator new[] (const size_t uSize, const z::Alignment& alignment);

/// <summary>
/// Overload for delete operator to get dynamic deallocation of aligned memory blocks.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the aligned memory block to be deallocated.</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
Z_LAYER_COMMON_SYMBOLS void operator delete (void* pMemoryBlock, const z::Alignment& alignment);

/// <summary>
/// Overload for delete[] operator to get dynamic deallocation aligned memory blocks, grouped as arrays.
/// </summary>
/// <param name="pMemoryBlock">[IN] Pointer to the first aligned memory block of the whole to be deallocated.</param>
/// <param name="alignment">[IN] The data alignment value (must be always a power of two).</param>
Z_LAYER_COMMON_SYMBOLS void operator delete[] (void* pMemoryBlock, const z::Alignment& alignment);


#endif // __ALLOCATIONOPERATORS__
