#ifndef SOY_VIRTUAL_MEMORY_H
#define SOY_VIRTUAL_MEMORY_H

#include "soycore.h"

typedef enum enum_memState {
	UNINITIALIZED = 0,
	INITIALIZED = 1
} memState;


typedef struct tag_virtualMemory {
	int64 size;
	void* storage;
	memState state;
} virtualMemory;


flag init_memory(virtualMemory* memory) {
	memory->UNINITIALIZED;
	memory->size = Megabytes(256);
	memory->storage = VirtualAlloc(0, memory->size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);


	return TRUE;
}

flag soy_vm_update_memory(virtualMemory* memory) {
	

	if(memory->state != INITIALIZED) {
		init_memory(memory);
	}


	return TRUE;
}


#endif
