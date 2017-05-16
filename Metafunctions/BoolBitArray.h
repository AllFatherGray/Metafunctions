#pragma once
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "SimpleMetaFunctions.h"

struct IBoolArray
{
	virtual void Resize(size_t Size = 1) = 0;
	virtual bool operator[](unsigned index) = 0;
	virtual void set(unsigned index, bool b) = 0;
	unsigned capacity()const
	{
		return length;
	}
	unsigned count()const
	{
		return Size;
	}

protected:
	unsigned length;
	unsigned Size;
};
template<class T>
class BoolBitArray : public IBoolArray
{
	T* batchArray;
public:
	// NUmber of Bits T can represent per instance
	static const unsigned BatchSize = sizeof(T) * 8;
	static const T Lower = BitGenerator<(BatchSize / 2) - 1, BatchSize>::value;
	static const T Upper = ~Lower;
	static const T True = Upper + Lower;
	static const T False = ~True;
	BoolBitArray(size_t Size = 1, bool initialState = false)
	{
		assert(Size > 0);
		this->Size = Size;
		length = ((unsigned)ceil((Size - 1) / BatchSize)) + 1;// 2 / 4
		batchArray = new T[length];
		for (int i = 0; i < length; ++i)
			batchArray[i] = initialState ? True : False;
	}

	bool operator[](unsigned index)
	{
		assert(index < Size);
		return  ((batchArray[index / BatchSize] >> index) & 1);
	}
	void set(unsigned index, bool b)
	{
		assert(index < Size);
		batchArray[index / BatchSize] ^= (-(b) ^ batchArray[index / BatchSize]) & (1 << (index % BatchSize));
	}
	void Resize(size_t Size = 1)
	{
		assert(Size > 0);
		if (this->Size != Size)
		{
			unsigned length = ((unsigned)ceil((Size - 1) / BatchSize)) + 1;
			if (this->length != length)
			{
				T* newArr = new T[length];
				int* p, *o;
				//std::copy(p, p + 10, o);
				//std::copy(batchArray, batchArray/*(batchArray + std::min(this->length, length))*/, newArr);
				//std::copy(batchArray, batchArray, newArr);
				delete[] batchArray;
				batchArray = newArr;
			}
			this->Size = Size;
		}
	}
#pragma region Print Methods - Testing Purposes only
	void print()
	{
		for (unsigned i = 0; i < length; ++i)
		{
			for (unsigned j = 0; j < BatchSize; ++j)
			{
				std::cout << ((batchArray[(i * BatchSize) / BatchSize] >> j) & 1) << " ";
			}
			std::cout << std::endl;
		}
	}
	static void print(const T& data)
	{
		for (unsigned j = 0; j < BatchSize; ++j)
		{
			std::cout << ((data >> j) & 1) << " ";
		}
		std::cout << std::endl;
	}
	static void printUpper()
	{
		return print(Upper);
	}
	static void printLower()
	{
		return print(Lower);
	}
#pragma endregion
};