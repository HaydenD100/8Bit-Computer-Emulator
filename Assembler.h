#pragma once
#include "main.cpp"
#include "array"

//THIS ISNT WORKING YET


struct Assembler
{
	//mnemonic
	const char* opCodes[16] = { "null", "ADD","ADC","AND","OR","NOT","CMP","LR","WR","JMP","JMF","SUB","null","null","IP","OP" };
	const char* registers[7] = { "A","B","C","D","E","G","H" };
	const char* flags[6] = { "l","e","c","o","z","n" };

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

			uint8_t flag;

			uint8_t reg1 = 255;
			uint8_t reg2 = 255;

			uint16_t Address;

			string temp;
			string strReg;

			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ' ') {
					break;
				}
				temp.push_back(line[i]);
			}

			for (int i = 0; i < 16; i++) {
				if (temp == opCodes[i]) {
					opCode = i;
				}
			}
			int i = temp.length();
			temp.clear();
			temp = line[i + 1];
			for (int i = 0; i < 7; i++) {
				if (temp == registers[i]) {
					reg1 = i;
				}
			}
			if (i + 3 <= line.length())
			{
				temp.clear();
				temp = line[i + 3];
				for (int i = 0; i < 7; i++) {
					if (temp == registers[i] && i != reg1) {
						reg2 = i;
					}
				}

			}
			cout << "Opcode:" << (int)opCode << " Reg1:" << (int)reg1 << " Reg2:" << (int)reg2;







			/*
			if (opCode == NULL) {
				cout << "ERROR OPCODE NOT FOUND";
			}
			Data[outputLine] = opCode;

			switch (opCode)
			{
			case ADD: {
				break;
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
			*/
		}
	}
};