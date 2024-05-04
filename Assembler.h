#include <string>
#include <vector>

using namespace std;

struct Assembler
{
	vector<uint8_t> Assemble(string path) {
		uint16_t MemoryStart = 0xe000;

		//stores the adress of jump points
		vector<string> jmpKeyWords;
		vector<uint16_t> jmpAddress;

		uint16_t EndAddress;

		//requests
		vector<string> jmpKeyWordsReq;
		vector<int> jmpAddressReq;
		

		vector<uint8_t> machineCode;

		std::ifstream file(path);
		std::string line;
		int currentLine = 1;

		while (std::getline(file, line))
		{
			vector<string> tokenizedString;

			//lexer
			string token = "";
			for (char x : line)
			{
				if (x != ' ') {
					token = token + x;
				}
				else {
					if (token.size() <= 0)
						continue;
					tokenizedString.push_back(token);
					token = "";
					
				}
				if (x == line[line.length() - 1] && token != "" && token.size() > 0) {
					tokenizedString.push_back(token);
					token = "";
				}
			}

			


			//stores the memory address of a jump point;
			if (tokenizedString[0][tokenizedString[0].length() - 1] == ':') {
				string keyWord = tokenizedString[0].substr(0, tokenizedString[0].length() - 1);
				jmpKeyWords.push_back(keyWord);
				jmpAddress.push_back(MemoryStart + machineCode.size() - 1);
			}
			
			

			if (tokenizedString[0][0] == '/') {
				continue;
			}
			
			if (tokenizedString[0] == "ADD") {
				
				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b00010000 + accumReg;
					machineCode.push_back(byte);
					
					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {
					
					uint8_t byte = 0b00011000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "ADC") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b00100000 + accumReg;
					machineCode.push_back(byte);

					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {

					uint8_t byte = 0b00101000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "AND") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b00110000 + accumReg;
					machineCode.push_back(byte);

					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {

					uint8_t byte = 0b00111000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "OR") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b01000000 + accumReg;
					machineCode.push_back(byte);

					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {

					uint8_t byte = 0b01001000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "NOT") {
				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}
				uint8_t byte = 0b01010000 + accumReg;
				machineCode.push_back(byte);
			}

			if (tokenizedString[0] == "CMP") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b01100000 + accumReg;
					machineCode.push_back(byte);

					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {

					uint8_t byte = 0b01101000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "LR") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t value = 0;
				uint16_t addr = 0;
				//if parm2 is a value
				if(tokenizedString[2][0] == '#') {

					if (tokenizedString[2][1] == '$') {
						tokenizedString[2].erase(0, 2);
						const char* chartoString = tokenizedString[2].c_str();
						addr = (uint16_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][1] == '%') {
						tokenizedString[2].erase(0, 2);
						const char* chartoString = tokenizedString[2].c_str();
						addr = (uint16_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b01111000 + accumReg;
					machineCode.push_back(byte);
					byte = addr >> 8;
					machineCode.push_back(byte);
					byte = addr;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						value = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						value = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b01110000 + accumReg;
					machineCode.push_back(byte);
					byte = value;
					machineCode.push_back(byte);
					
				}
			}

			if (tokenizedString[0] == "WR") {
				int8_t value = GetReg(tokenizedString[1]);
				if (value == 10) {
					if (tokenizedString[1][0] == '$') {
						tokenizedString[1].erase(0, 1);
						const char* chartoString = tokenizedString[1].c_str();
						value = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[1][0] == '%') {
						tokenizedString[1].erase(0, 1);
						const char* chartoString = tokenizedString[1].c_str();
						value = (int8_t)strtol(chartoString, NULL, 2);
					}
					uint8_t byte = 0b10000000;
					machineCode.push_back(byte);
					byte = value;
					machineCode.push_back(byte);
				}
				else {
					uint8_t byte = 0b10001000 + value;
					machineCode.push_back(byte);
				}
				uint16_t addr;

				if (tokenizedString[2][0] == '#') {

					if (tokenizedString[2][1] == '$') {
						tokenizedString[2].erase(0, 2);
						const char* chartoString = tokenizedString[2].c_str();
						addr = (uint16_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][1] == '%') {
						tokenizedString[2].erase(0, 2);
						const char* chartoString = tokenizedString[2].c_str();
						addr = (uint16_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = addr >> 8;
					machineCode.push_back(byte);
					byte = addr;
					machineCode.push_back(byte);
				}
				else {
					cout << "ERROR address is incorrect," << " line:" << currentLine << endl;
					break;
				}
			}

			if (tokenizedString[0] == "JMP") {

				uint16_t addr = 0;

				for (int i = 0; i < jmpKeyWords.size(); i++) {
					if (jmpKeyWords[i] == tokenizedString[1]) {
						addr = jmpAddress[i];
						break;

					}
				}
				if (addr == 0) {

					jmpKeyWordsReq.push_back(tokenizedString[1]);
					jmpAddressReq.push_back(machineCode.size() + 1);
				}
				

				uint8_t byte = 0b10010000;
				machineCode.push_back(byte);
				byte = addr >> 8;
				machineCode.push_back(byte);
				byte = addr;
				machineCode.push_back(byte);

			}

			if (tokenizedString[0] == "JMF") {
				

				uint16_t addr = 0;
				uint16_t flag = GetFlag(tokenizedString[1]);

				if (flag == 10) {
					cout << "ERROR flag not found," << " line:" << currentLine << endl;
					break;
				}

				for (int i = 0; i < jmpKeyWords.size(); i++) {
					if (jmpKeyWords[i] == tokenizedString[2]) {
						addr = jmpAddress[i];
						break;
						
					}
				}
				if (addr == 0) {

					jmpKeyWordsReq.push_back(tokenizedString[2]);
					jmpAddressReq.push_back(machineCode.size() + 1);
				}

				uint8_t byte = 0b10100000 + flag;
				machineCode.push_back(byte);
				byte = addr >> 8;
				machineCode.push_back(byte);
				byte = addr;
				machineCode.push_back(byte);



			}

			if (tokenizedString[0] == "SUB") {

				uint8_t accumReg = GetReg(tokenizedString[1]);
				if (accumReg == 10) {
					cout << "ERROR Register not found," << " line:" << currentLine << endl;
					break;
				}

				int8_t parm2 = GetReg(tokenizedString[2]);
				//if parm2 is a value
				if (parm2 == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm2 = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR second paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b10110000 + accumReg;
					machineCode.push_back(byte);

					byte = parm2;
					machineCode.push_back(byte);
				}
				//if parm2 is a reg
				else {

					uint8_t byte = 0b10111000 + accumReg;
					machineCode.push_back(byte);
					byte = parm2;
					machineCode.push_back(byte);
				}
			}

			if (tokenizedString[0] == "PUSH") {
				int8_t parm = GetReg(tokenizedString[1]);
				if (parm == 10) {
					if (tokenizedString[2][0] == '$') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm = (int8_t)strtol(chartoString, NULL, 16);
					}
					else if (tokenizedString[2][0] == '%') {
						tokenizedString[2].erase(0, 1);
						const char* chartoString = tokenizedString[2].c_str();
						parm = (int8_t)strtol(chartoString, NULL, 2);
					}
					else {
						cout << "ERROR PUSH paramter incorrect," << " line:" << currentLine << endl;
						break;
					}
					uint8_t byte = 0b11000000;
					machineCode.push_back(byte);

					byte = parm;
					machineCode.push_back(byte);
				}
				else {
					uint8_t byte = 0b11001000 + parm;
					machineCode.push_back(byte);
				}
			}
			if (tokenizedString[0] == "POP") {
				uint8_t reg = GetReg(tokenizedString[1]);
				if (reg == 10) {
					cout << "ERROR reg not found," << " line:" << currentLine << endl;
					break;
				}

				uint8_t byte = 0b11010000 + reg;
				machineCode.push_back(byte);
			}

			if (tokenizedString[0] == "IP") {
				uint8_t reg = GetReg(tokenizedString[1]);
				if (reg == 10) {
					cout << "ERROR reg not found," << " line:" << currentLine << endl;
					break;
				}

				uint8_t byte = 0b11100000 + reg;
				machineCode.push_back(byte);
			}

			if (tokenizedString[0] == "OP") {
				uint8_t reg = GetReg(tokenizedString[1]);
				if (reg == 10) {
					uint8_t byte = 0b11110000;
					machineCode.push_back(byte);
					byte = line.size() - 3;
					machineCode.push_back(byte);

					
					for (int w = 1; w < tokenizedString.size(); w++) {
						for (int c = 0; c < tokenizedString[w].size(); c++) {
							byte = tokenizedString[w][c];
							machineCode.push_back(byte);
						}
						if (w < tokenizedString.size() - 1) {
							byte = ' ';
							machineCode.push_back(byte);
						}
					}
				}
				else {
					uint8_t byte = 0b11111000 + reg;
					machineCode.push_back(byte);
				}
				
			}
			currentLine++;

			
		}
		uint16_t addr = 0;
		for (int jr = 0; jr < jmpKeyWordsReq.size();jr++) {
			for (int i = 0; i < jmpKeyWords.size(); i++) {
				if (jmpKeyWords[i] == jmpKeyWordsReq[jr]) {
					
					addr = jmpAddress[i];
					uint8_t byte = addr >> 8;
					machineCode[jmpAddressReq[jr]] = byte;
					byte = addr;
					machineCode[jmpAddressReq[jr] + 1] = byte;


				}
			}
			if (addr == 0) {
				cout << "ERROR Jump point:" << jmpKeyWordsReq[jr] << "Not Found" << endl;
			}

		}
		
		//This will print out the complied machine code for debugging purposes
		/*
		for (int i = 0; i < machineCode.size(); i++) {
			cout <<"0x" << hex << (int)machineCode[i] << endl;
		}
		*/
		
		
		


		
		
		return machineCode;
		
	}

	uint8_t GetReg(string reg) 
	{
		if (reg == "A") return 0;
		else if (reg == "B") return 1;
		else if (reg == "C") return 2;
		else if (reg == "D") return 3;
		else if (reg == "E") return 4;
		else if (reg == "G") return 5;
		else if (reg == "H") return 6;
		else {
			return 10;
		}
	}

	uint8_t GetFlag(string reg)
	{
		if (reg == "LESS") return 0;
		else if (reg == "EQUALS") return 1;
		else if (reg == "CARRY") return 2;
		else if (reg == "OVERFLOW") return 3;
		else if (reg == "ZERO") return 4;
		else {
			return 10;
		}
	}
};