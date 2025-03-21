#pragma once
#include "Allocator.h"

class MemoryPool;
extern class Memory* GMemory;

class Memory
{
	enum
	{
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2024 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void* Allocate(int size);
	void Release(void* ptr);

private:
	vector<MemoryPool*> _pools;
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));
	new(memory)Type(forward<Args>(args)...);
	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	obj->~Type();
	PoolAllocator::Release(obj);
}

template<typename Type, typename... Args>
shared_ptr<Type> MakeShared(Args&&... args)
{
	return shared_ptr<Type>{ new Type(forward<Args>(args)...) };
}