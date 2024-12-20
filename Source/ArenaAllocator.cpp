#include "ArenaAllocator.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static constexpr auto MIN_PROGRAM_MEMORY = 2048;
static constexpr auto MAX_PROGRAM_MEMORY = 4096;

ArenaAllocator::ArenaAllocator()
{
	heap_arena = HeapCreate(0, MIN_PROGRAM_MEMORY, MAX_PROGRAM_MEMORY);
}

ArenaAllocator::~ArenaAllocator()
{
	HeapDestroy(heap_arena);
	heap_arena = nullptr;
}

void* ArenaAllocator::Allocate(memsize_t size)
{
	//
	// TODO: Implement Arena!
	//
	return HeapAlloc(heap_arena, 0, size);
}

void ArenaAllocator::Deallocate(void* data)
{
	//
	// TODO: Implement Arena!
	//
	HeapFree(heap_arena, 0, data);
}