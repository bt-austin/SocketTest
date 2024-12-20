#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H

typedef unsigned long long int memsize_t;

class ArenaAllocator
{
public:

	ArenaAllocator();
	~ArenaAllocator();

	void* Allocate(memsize_t size);
	void Deallocate(void* data);

private:

	void* heap_arena;

};

#endif // !ARENA_ALLOCATOR_H