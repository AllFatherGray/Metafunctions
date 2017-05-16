#pragma once
// Metafunctions for simple problems without constexpr.

#pragma region Pow
template<unsigned N, unsigned P>
struct Pow
{
	enum { value = N * Pow<N, P - 1>::value };
};
template<unsigned N>
struct Pow<N, 1>
{
	enum { value = N };
};
template<unsigned N>
struct Pow<N, 0>
{
	enum { value = 1 };
};
#pragma endregion

#pragma region BitGenerator
// Sets all the bits of S to the Nth power. Ex S/2 , S will fill the lower bits
template <unsigned N, unsigned S>
struct BitGenerator
{
	enum
	{
		value = ((-(true) ^ 0) & (1 << ((N) % S))) + BitGenerator<N - 1,S>::value
	};
};
template <unsigned S>
struct BitGenerator<0, S>// Halts Generator
{
	enum {
		value = ((-(true) ^ 0) & (1 << ((0) % S)))
	};
};
#pragma endregion

#pragma region Clamp
//Keeps N within bounds of MIN and MAX
template<unsigned N, unsigned MIN, unsigned MAX>
struct Clamp
{
	enum 
	{
		value =
		N < MIN ? MIN : // if N is lower than MIN return MIN
		N > MAX ? MAX :  // else if N is higher than MAX return MAX
		N // else return N
	};
};
#pragma endregion

#pragma region Factorial
// Source : https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Metafunction
template <int N>
struct Factorial
{
	enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0>
{
	enum { value = 1 };
};
#pragma endregion