#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Assembler.h"
#include "Memory.h"
#include "Graphics.h"






using namespace std;

enum Register
{
	A = 0x00,
	B = 0x01,
	C = 0x02,
	D = 0x03,
	E = 0x04,
	G = 0x05,
	H = 0x06,
};


enum opCode
{
	ADD = 0x1,
	ADC = 0x2,
	AND = 0x3,
	OR = 0x4,
	NOT = 0x5,
	CMP = 0x6,
	LR = 0x7,
	WR = 0x8,
	JMP = 0x9,
	JMF = 0xa,
	SUB = 0xb,
	PUSH = 0xc,
	POP = 0xd,
	IP = 0xe,
	OP = 0xf
};

enum Flags
{
	l = 0x00,
	e = 0x01,
	c = 0x02,
	o = 0x03,
	z = 0x04,
};






struct CPU
{
	//Program Counter
	uint16_t PC;
	//Stack pointer (points to next spot on stack) 
	uint16_t SP;
	//Insctrution register
	uint8_t IR;

	//Register
	uint8_t Register[7] = { 0,0,0,0,0,0,0 };


	//Flag Register l,e,c,o,z,n,null,null
	uint8_t F;


	void Initialize(Memory& memory) {
		F = 0;
		SP = 0xffff;
		PC = 0xe000; // Starts program pointer at memory address 57344
		memory.Initialize();


	}

	void Execute(Memory& memory) {
		IR = memory.ReadByte(PC);

		uint8_t opCode = IR >> 4;
		uint8_t valueTwo = NULL;
		switch (opCode)
		{
		case ADD: {
			uint8_t reg = IR & 0b00000111;

			int8_t value1 = Register[reg];
			int8_t value2 = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value2 = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value2 = memory.ReadByte(PC);
			}

			//sets overflow flag is their is an error
			int8_t overFlowCheck = value1 + value2;
			if (value1 + value2 != overFlowCheck) {
				F = F | 0b00010000;
			}
			else {
				F = F & 0b11101111;
			}

			//carry check
			uint16_t carryCheck = value1 + value2;
			if (carryCheck > 0b11111111) {
				F = F | 0b00100000;
			}
			else {
				F = F & 0b11011111;
			}

			Register[reg] = overFlowCheck;
			break;
		}
		case ADC: {
			uint8_t reg = IR & 0b00000111;

			int8_t value1 = Register[reg];
			uint8_t value2 = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value2 = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value2 = memory.ReadByte(PC);
			}

			if ((F = F & 0b00100000) == 32) {
				Register[reg] = value1 + value2 + 0b100000000;
			}
			else {
				Register[reg] = value1 + value2;
			}

			//set carry flag to 0
			F = F & 11011111;
			break;
		}
		case AND: {
			uint8_t reg = IR & 0b00000111;
			uint8_t value = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value = memory.ReadByte(PC);
			}
			Register[reg] = Register[reg] & value;

			break;
		}
		case OR: {
			uint8_t reg = IR & 0b00000111;
			uint8_t value = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value = memory.ReadByte(PC);
			}
			Register[reg] = Register[reg] | value;
			break;
		}
		case NOT: {
			uint8_t reg = IR & 0b00000111;

			Register[reg] = ~Register[reg];
			break;
		}
		case CMP: {
			uint8_t reg = IR & 0b00000111;
			int8_t value = NULL;
			int valueReg = Register[reg];
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value = memory.ReadByte(PC);
			}
			if (valueReg == value)
				F = F | 01000000;
			else {
				F = F & 10111111;
			}
			if (valueReg < value)
				F = F | 10000000;
			else {
				F = F & 01111111;
			}

			if (valueReg == 0)
				F = F | 00001000;
			else {
				F = F & 11110111;
			}
			break;
		}
		case LR: {
			uint8_t parm = IR & 0b00001111;

			uint8_t reg = IR & 0b00000111;
			uint8_t value = NULL;
			if ((IR & 0b00001000) == 0b00000000)
			{

				PC++;
				value = memory.ReadByte(PC);
			}
			else {
				PC++;
				uint16_t address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address += memory.ReadByte(PC);
				value = memory.ReadByte(address);
			}

			Register[reg] = value;
			break;
		}
		case WR: {
			uint8_t parm = IR & 0b00001111;
			uint8_t reg = NULL;
			uint8_t value = NULL;
			uint16_t address;

			if ((IR & 0b00001111) == 0b00000000)
			{
				PC++;
				value = memory.ReadByte(PC);
				PC++;
				address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address += memory.ReadByte(PC);
			}
			else if ((IR & 0b00001111) == 0b00000001) {
				PC++;
				value = memory.ReadByte(PC);
				PC++;
				address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address = Register[memory.ReadByte(PC)];
			}
			else if ((IR & 0b00001111) == 0b00001000) {
				PC++;
				value = Register[memory.ReadByte(PC)];
				PC++;
				address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address += memory.ReadByte(PC);
			}
			else if ((IR & 0b00001111) == 0b00001001) {
				PC++;
				value = Register[memory.ReadByte(PC)];
				PC++;
				address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address = address + Register[memory.ReadByte(PC)];
				
			}

			memory.WriteByte(address, value);
			break;
		}
		case JMP: {
			PC++;
			uint16_t address = memory.ReadByte(PC);
			address = address << 8;
			PC++;
			address += memory.ReadByte(PC);
			PC = address;
			break;
		}
		case JMF: {
			uint8_t flag = IR & 0b00000111;
			if ((((F << flag) & 0b10000000) == 0b10000000))
			{
				PC++;
				uint16_t address = memory.ReadByte(PC);
				address = address << 8;
				PC++;
				address += memory.ReadByte(PC);
				PC = address;
			}
			else {
				PC++;
				PC++;
			}
			

			break;
		}
		case SUB: {
			uint8_t reg = IR & 0b00000111;
			int8_t value1 = Register[reg];
			int8_t value2 = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				PC++;
				value2 = Register[memory.ReadByte(PC)];
			}
			else {
				PC++;
				value2 = memory.ReadByte(PC);
			}

			value2 = ~(value2)+0b00000001;

			//sets overflow flag is their is an error
			int8_t overFlowCheck = value1 + value2;
			if (value1 + value2 != overFlowCheck) {
				F = F | 0b00010000;
			}
			else {
				F = F & 0b11101111;
			}

			Register[reg] = overFlowCheck;
			break;
		}

		case PUSH: {
			uint8_t reg = IR & 0b00000111;
			int8_t value = NULL;
			if ((IR & 0b00001000) == 0b00001000)
			{
				value = Register[reg];
			}
			else {
				PC++;
				value = memory.ReadByte(PC);
			}

			memory.WriteByte(SP, value);
			SP--;
			break;
		}
		case POP: {
			if (SP >= 0xffff)
				break;
			SP++;
			uint8_t reg = IR & 0b00000111;
			Register[reg] = memory.ReadByte(SP);


			break;
		}
		case IP: {
			int input; //This is need as cin dosent work with uint8_t
			uint8_t reg = IR & 0b00000111;

			cin >> input;
			Register[reg] = input;
			break;

		}
		case OP: {
			
			
			uint8_t reg = IR & 0b00000111;
			int stringSize = 0;
			if ((IR & 0b00001000) == 0b00001000)
			{
				cout << (int)(int8_t)Register[reg] << endl;
				break;
			}
			
			PC++;
			stringSize = memory.ReadByte(PC);
			for (int i = 0; i < stringSize; i++) {
				PC++;
				cout << memory.ReadByte(PC);
			}
			cout << endl;
		}

		default:
			break;
		}
		PC++;

	}

};



int main(int argc, const char* argv[]) {

	
	CPU cpu;
	Memory memory;
	Assembler assembler;

	Graphics graphicsCard;
#

	cpu.Initialize(memory);
	graphicsCard.Initialize();

	
	//vector<uint8_t> mCode = assembler.Assemble("..\\..\\TestCode.txt");
	vector<uint8_t> mCode = assembler.Assemble("C:\\Users\\kokok\\OneDrive\\Desktop\\Code\\Home\\C++\\Test-8\\TestCode.txt");

	
	
	for (int i = 0; i < mCode.size(); i++) {
		memory.WriteByte(0xE000 + i, mCode[i]);
	}

	while (true) {

		cpu.Execute(memory);

		graphicsCard.UpdateColour(memory);
		graphicsCard.GetInput(memory);

		if (memory.ReadByte(0x0002) == 1)
			break;
		//cout << "last insctruction:0x" << hex << (int)cpu.IR << endl;

	}
	
	graphicsCard.DestoryWindow();



	return 1;
}