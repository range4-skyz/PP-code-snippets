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
// - GCC/Clang/MinGW/MSVC(x86-64): https://godbolt.org/z/c67hx8757

//// ---- Key Points:
//

/* clang-format on */

#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

#include <stddef.h> // for size_t

#ifndef PP_ASSERT
    #include <assert.h>
    #define PP_ASSERT assert
#endif /* PP_ASSERT */

/* Get the array length and index value */
#define ARRAY_LEN(array)        ( sizeof( array ) / sizeof( array[0] ) )
#define ARRAY_GET(array, index) ( PP_ASSERT( (size_t)index < ARRAY_LEN( array ) ), array[(size_t)index] )

/* Convert a macro argument into a string constant */
#define TOSTRING_IMPL(x) #x
#define TOSTRING(x) TOSTRING_IMPL( x )

/* Merge two tokens into one while expanding macros */
#define CONCAT_IMPL(l, r) l ## r
#define CONCAT(l, r) CONCAT_IMPL( l, r )

/* Merge more two tokens into one while expanding macros */
#define CONCAT_N_IMPL(l, ...) l ## __VA_ARGS__
#define CONCAT_N(l, ...) CONCAT_N_IMPL( l, __VA_ARGS__ )

#define L_PAREN (
#define R_PAREN )
#define LR_PARENS ()

/* Implement nested macro calls using argument pre-scanning
 * Rescan once time */
#define EXPAND(x) x
#define EXPAND_N(...) __VA_ARGS__

/* Implement nested macro calls using argument pre-scanning
   Rescan multiple times */
#define EXPAND_N_SUPER(...)   EXPAND_S1_N( EXPAND_S1_N( EXPAND_S1_N( EXPAND_S1_N( __VA_ARGS__ ) ) ) )
#define EXPAND_S1_N(...)      EXPAND_S2_N( EXPAND_S2_N( EXPAND_S2_N( EXPAND_S2_N( __VA_ARGS__ ) ) ) )
#define EXPAND_S2_N(...)      EXPAND_S3_N( EXPAND_S3_N( EXPAND_S3_N( EXPAND_S3_N( __VA_ARGS__ ) ) ) )
#define EXPAND_S3_N(...)      EXPAND_S4_N( EXPAND_S4_N( EXPAND_S4_N( EXPAND_S4_N( __VA_ARGS__ ) ) ) )
#define EXPAND_S4_N(...)      __VA_ARGS__

#endif /* BASE_MACROS_H_ */
