/* clang-format off */

// MIT License
//
// Copyright (c) 2025 sStmtz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//// ---- References:
// - https://gcc.gnu.org/onlinedocs/cpp/Macros.html
//
// - https://www.ashn.dev/blog/2020-01-06-c-array-length.html

//// ---- Godbolt Tests:
// - GCC/Clang/MinGW/MSVC(x86-64): https://godbolt.org/z/95enqYbs6

//// ---- Key Points:
//

/* clang-format on */

#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

#include <assert.h> // for assert(expr)
#include <stdint.h> // for size_t

#define TOSTRING_IMPL(x) #x
#define TOSTRING(x) TOSTRING_IMPL( x )

#define CONCAT_IMPL(l, r) l##r
#define CONCAT(l, r) CONCAT_IMPL( l, r )

#define ARRAY_LEN(array)        ( sizeof( array ) / sizeof( array[0] ) )
#define ARRAY_GET(array, index) ( assert( ( size_t )index < ARRAY_LEN( array ) ), array[( size_t )index] )

#endif /* BASE_MACROS_H_ */
