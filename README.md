

8 bit 
1 ADD reg,reg/8bit reg = reg + reg/8bit
2 ADC reg,reg/8bit reg = reg + reg/8bit + c
3 AND reg,reg/8bit
4 OR  reg,reg/8bit
5 NOT reg
6 CMP reg,reg/8bit Reg get comapred against reg/8bit and sets flags (l,e,z)
7 LR reg, 8bit/addr Loads value or value at memory address into register
8 WR reg/8bit, addr Writes register or 8bit value to memory
9 JMP addr sets PC to addr
a JMF flag addr sets pc to addr if inputed flag is set XXXX_YYY YYY = flag code
b SUB reg,reg/8bit reg = reg - reg/8bit
c 
d 
e IP reg Puts input from input device(terminal) into register
f OP reg Outputs register into output device(terminal)


LAYOUR
XXXXYZZZ

ADDRESS LAYOUT IN MEMORY

XXXXXXXXYYYYYYYY

YYYYYYYY
XXXXXXXX


X: 4 bit instruction code
Y: 0 if argument is value, 1 if argument is a register or address if its 8bit/addr
Z: Register/Flag



REGISTERS

General Purpose
A 
B
C
D
E
G
H

Flag register
l = 0x0 lessthen
e = 0x1 equals
c = 0x2 carry
o = 0x3 overflow
z = 0x4 zero
n = 0x5 negative
