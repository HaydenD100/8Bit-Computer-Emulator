#pragma once
#include "main.cpp"
#include "array"

struct Assembler
{
	//mnemonic
	string opCodes[16] = { "null", "ADD","ADC","AND","OR","NOT","CMP","LR","WR","JMP","JMF","SUB","null","null","IP","OP" };
	string registers[7] = { "A","B","C","D","E","G","H" };
	string flags[6] = { "l","e","c","o","z","n" };

	int outputLine = 0;
	//Maximum amount of lines of code
	uint8_t Data[8191];



	void Assemble(string path) {
		std::ifstream file(path);
		std::string line;
		int CurrentLine = 0;
		while (std::getline(file, line))
		{
			uint8_t opCode = NULL;
			bool UsingRegister = false;
			uint8_t reg2;
			uint16_t Address;

			for (int i = 0; i < opCodes->size(); i++) {
				if (line.find(opCodes[i])) {
					opCode = i;
				}
			}
			for (int i = 0; i < registers->size(); i++) {
				if (line.substr(line.length() - 1, line.length()).compare(registers[i])) {
					reg2 = i;
					UsingRegister = true;
				}
			}
			if (opCode == NULL) {
				cout << "ERROR OPCODE NOT FOUND";
			}
			Data[outputLine] = opCode;

			switch (opCode)
			{
			case ADD: {
			}
			case ADC: {

				break;
			}
			case AND: {

				break;
			}
			case OR: {

				break;
			}
			case NOT: {

				break;
			}
			case CMP: {

				break;
			}
			case LR: {

				break;
			}
			case WR: {

				break;
			}
			case JMP: {

				break;
			}
			case JMF: {
				break;
			}
			case IP: {

				break;
			}
			case OP: {

				break;
			}
			case SUB: {

				break;
			}
			default:
				break;


			}
		}
	}
};