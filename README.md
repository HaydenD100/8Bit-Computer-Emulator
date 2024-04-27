
```
------Info-------
Big endian
7 General purpose 8-bit register + Flags register [l,e,c,o,z,n,0,0]
16-bit memory address for 65535bytes of memory or 64KB
16 instructions



------Instructions---------
0x1 ADD reg,reg/8bit		reg = reg + reg/8bit
0x2 ADC reg,reg/8bit		reg = reg + reg/8bit + c
0x3 AND reg,reg/8bit		reg = reg & reg/8bit
0x4 OR  reg,reg/8bit		reg = reg | reg/8bit
0x5 NOT reg					reg = ~reg
0x6 CMP reg, reg/8bit		Reg get comapred against reg/8bit and sets flags (l,e,z)
0x7 LR reg, 8bit/addr		Loads value or value at memory address into register
0x8 WR reg/8bit, addr		Writes register or 8bit value to memory
0x9 JMP addr				sets PC to addr
0xa JMF flag, addr			sets PC to addr if inputed flag is set flag number XXXX0YYY YYY = flag code
0xb SUB reg, reg/8bit		reg = reg - reg/8bit
0xc 
0xd 
0xe IP reg					Puts input from input device(terminal) into register
0xf OP reg					Outputs register into output device(terminal)



--------MACHINE CODE LAYOUT----------
XXXXYZZZ AAAAAAAA BBBBBBBB

X: 4 bit instruction code
Y: 0 if argument is value, 1 if argument is a register or address if its 8bit/addr
Z: Register/Flag
A: Second paramter (flag/register/value) or first byte of 16bit address
B: Second byte of 16bit address



----------REGISTERS---------
General Purpose
A 0x0
B 0x1
C 0x2
D 0x3
E 0x4
G 0x5
H 0x6

Flag
[l,e,c,o,z,n,0,0]

l 0x0 LESS
e 0x1 EQUALS
c 0x2 CARRY
o 0x3 OVERFLOW
z 0x4 ZERO
n 0x5 NEGATIVE
```