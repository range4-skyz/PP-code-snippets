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
// - https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// - https://en.cppreference.com/w/cpp/preprocessor/replace
//
// - https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
// - https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
// - https://stackoverflow.com/questions/26682812/argument-counting-macro-with-zero-arguments-for-visualstudio
// - https://gist.github.com/aprell/3722962

//// ---- Godbolt Tests:
// - GCC/Clang/MinGW(x86-64): https://godbolt.org/z/EMn8evrEx [ -E ]
// - MSVC(x64/x86)          : https://godbolt.org/z/Yaq7hehfr [ /Zc:preprocessor /Zc:__cplusplus /std:c++20 ]

//// ---- Key Points:
// - Q: How to handle zero arguments for variadic parameters ???
// A1. , ##__VA_ARGS__            (from GCC extension), But MSVC not supports it :(
// A2. __VA_OPT__(,) __VA_ARGS__ (since C++20)

/* clang-format on */

#ifndef VA_NARGS_H_
#define VA_NARGS_H_

#define CONCAT_IMPL(l, r) l##r
#define CONCAT(l, r) CONCAT_IMPL( l, r )

// clang-format off
#define VA_ARGS_N_0(_0,                       \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63, N,...) N

#define VA_ARGS_N_1( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63, N,...) N

// Reverse-sequence count list
#define VA_RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0
// clang-format on

/* Count the number of variadic macro arguments
- Usage:
+----------------------------------------------------------+
|    #if defined(__cplusplus) && __cplusplus >= 202002L    |
|        VA_NARGS()       // -> 0                          |
|    #endif                                                |
|                                                          |
|    VA_NARGS(A)          // -> 1                          |
|    VA_NARGS(A,B)        // -> 2                          |
|    VA_NARGS(A,B,C)      // -> 3                          |
|    VA_NARGS(A,B,C,D)    // -> 4                          |
|    VA_NARGS(A,B,C,D,E)  // -> 5                          |
|    VA_NARGS(1,2,3,4,5,6,7,8,9,0,                         |
|         1,2,3,4,5,6,7,8,9,0,                             |
|         1,2,3,4,5,6,7,8,9,0,                             |
|         1,2,3,4,5,6,7,8,9,0,                             |
|         1,2,3,4,5,6,7,8,9,0,                             |
|         1,2,3,4,5,6,7,8,9,0,                             |
|         1,2,3)     // -> 63                              |
+----------------------------------------------------------+ */
#if defined(__GNUC__) || defined(__clang__)
    #define VA_NARGS_IMPL(...) VA_ARGS_N_0( __VA_ARGS__ )
    #if defined(__cplusplus) && __cplusplus >= 202002L
        #define VA_NARGS(...) VA_NARGS_IMPL( dummy __VA_OPT__(,) __VA_ARGS__, VA_RSEQ_N() )
    #else
        #define VA_NARGS(...) VA_NARGS_IMPL( dummy, ##__VA_ARGS__, VA_RSEQ_N() )
    #endif
#elif defined(_MSC_VER)
    #if defined(__cplusplus) && __cplusplus >= 202002L
        #define VA_NARGS_IMPL(...) VA_ARGS_N_0( __VA_ARGS__ )
        #define VA_NARGS(...) VA_NARGS_IMPL( dummy __VA_OPT__(,) __VA_ARGS__, VA_RSEQ_N() )
    #else
        /* NOTE: MSVC did not support zero arguments
                 for variadic macros before C++20 (__VA_OPT__) */
        #define VA_NARGS_IMPL(...) VA_ARGS_N_1( __VA_ARGS__ )
        #define VA_NARGS(...) VA_NARGS_IMPL( __VA_ARGS__, VA_RSEQ_N() )
    #endif
#else
    #define VA_NARGS(...)
#endif

/* Overloading API macros based on the number of arguments.
- Pros:
  - Inferred length parameter
  - Supports parameters of different types
- Cons:
  - Not type safe
- Uasge:
+-------------------------------------------------------------------------------+
|   #define FOO(...) FUNC_OVERLOAD_ON_NARGS(FOO, __VA_ARGS__)                   |
|   #define BAR(...) FUNC_OVERLOAD_ON_NARGS(BAR, __VA_ARGS__)                   |
|                                                                               |
|   #define FOO0() 0                                                            |
|   #define FOO1(x) x                                                           |
|   #define FOO2(x, y) ((x) + (y))                                              |
|   #define FOO3(x, y, z) ((x) + (y) + (z))                                     |
|                                                                               |
|   #if defined(__cplusplus) && __cplusplus >= 202002L                          |
|       FOO()           // expands to FOO0()        = 0                         |
|   #endif                                                                      |
|                                                                               |
|   FOO(a)              // expands to FOO1(a)       = a                         |
|   FOO(a, b)           // expands to FOO2(a, b)    = ((a) + (n))               |
|   FOO(a, b, c)        // expands to FOO3(a, b, c) = ((a) + (b) + (c))         |
|                                                                               |
|   BAR(a, 'b', 10, "Hello, World!", 3.14)                                      |
|   // -> expands to BAR5(a, 'b', 10, "Hello, World!", 3.14)                    |
+-------------------------------------------------------------------------------+ */
#define FUNC_OVERLOAD_ON_NARGS(prefix, ...) CONCAT( prefix, VA_NARGS( __VA_ARGS__ ) )( __VA_ARGS__ )

#endif /* VA_NARGS_H_ */
