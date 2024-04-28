#include <iostream>
#include <fstream>
#include <string>



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
	n = 0x05
};




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


	void Initialize(Memory &memory) {
		F = 0;
		SP = 0xffff; 
		PC = 0xe000; // Starts program pointer at memory address 57344
		memory.Initialize();


	}

	void Execute(Memory &memory) {
		IR = memory.ReadByte(PC);

		uint8_t opCode = IR >> 4;
		uint8_t valueTwo = NULL;
		switch (opCode)
		{
			case ADD: {

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
				if ((Register[reg] + value) > 0b11111111)
					F = F | 00100000;
				Register[reg] = Register[reg] + value;
				break;

			}
			case ADC: {
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
				Register[reg] = Register[reg] + value + (F & 0b00100000) >> 5;
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
				if(Register[reg] == value)
					F = F | 01000000;
				else {
					F = F & 10111111;
				}
				if (Register[reg] < value)
					F = F | 10000000; 
				else {
					F = F & 01111111;
				}

				if (Register[reg] == 0)
					F = F | 00001000;
				else {
					F = F & 11110111;
				}
				break;
			}
			case LR: {
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
				uint8_t reg = IR & 0b00000111;
				uint8_t value = NULL;
				uint16_t address = 0b0000000000000000;

				if ((IR & 0b00001000) == 0b00000000)
				{
					PC++;
					value = memory.ReadByte(PC);
					PC++;
					uint16_t address = memory.ReadByte(PC);
					address = address << 8;
					PC++;
					 address += memory.ReadByte(PC);
				}
				else {
					value = Register[reg];
					PC++;
					uint16_t address = memory.ReadByte(PC);
					address = address << 8;
					PC++;
					address += memory.ReadByte(PC);
				}

				memory.WriteByte(address, value);
				break;
			}
			case JMP: {
				PC++;
				uint16_t address = memory.ReadByte(PC);
				PC++;
				address += memory.ReadByte(PC);
				address = address << 8;

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
				break;
			}
			case SUB: {
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
				if (value > Register[reg])
					F = F | 0b00000100;
				else
					F = F & 0b11111011;
				value = ~(value)+0b00000001;
				uint16_t calculation = Register[reg] + value;
				if ((calculation & 0b0000000100000000) == 0b0000000100000000)
				{
					F = F | 0b00010000;
					calculation = calculation | 0b0000000010000000;
				}
				else {
					F = F & 0b11101111;
				}
				Register[reg] = (uint8_t)calculation;
				break;
			}

			case PUSH: {
				uint8_t reg = IR & 0b00000111;
				uint8_t value = NULL;
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
				if(SP >= 0xffff)
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
				cout << (int)Register[reg] << endl;
				break;
			}
			
			default:
				break;
		}
		PC++;	
	}

};



int main(int argc, const char* argv[]) {
	
	int start = 0xE000;
	CPU cpu;
	Memory memory;
	
	cpu.Initialize(memory);
	



	//push A onto stack
	memory.WriteByte(0xe002, 0b11000000);
	memory.WriteByte(0xe003, 0b00000011);
	//pop stack and put into B;
	memory.WriteByte(0xe004, 0b11010001);
	//print b to terminal
	memory.WriteByte(0xE005, 0b11110001);



	while (cpu.PC < 0xE010) {
		cpu.Execute(memory);
	}
		
	return 1;
}
