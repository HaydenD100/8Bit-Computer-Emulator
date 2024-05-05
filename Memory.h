#pragma once
#include "inttypes.h"

struct Memory
{
	static constexpr int MAX_MEMORY = 65536; //2^16
	uint8_t Data[MAX_MEMORY]; //255b of memory 

	void Initialize() {
		for (int i = 0; i < MAX_MEMORY; i++) {
			Data[i] = 0;
		}
	}

	uint8_t ReadByte(uint16_t address) {
		return Data[address];
	}
	void WriteByte(uint16_t address, uint8_t byte) {
		Data[address] = byte;
	}
};