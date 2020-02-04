#pragma once

#include "string.h"

template <typename T>
class TypeData
{
public:
	TypeData();
	~TypeData();
	//TypeData(const size_t size);
	//TypeData(void* buffer,const size_t size);
	//TypeData(const TypeData& x);
	TypeData<T>& operator=(const TypeData<T>& x);

	T* getData() const;
	size_t getSize() const;
private:
	T* data=nullptr;
	size_t size = 0;
};
