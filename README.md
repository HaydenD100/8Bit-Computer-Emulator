
```
------Info-------
Big endian
7 General purpose 8-bit register + Flags register [l,e,c,o,z,n,0,0]
16-bit memory address for 65535bytes of memory or 64KB
16 instructions



------Instructions---------
0x0 
0x1 ADD reg,8bit/reg		reg = reg + reg/8bit
0x2 ADC reg,8bit/reg		reg = reg + reg/8bit + c
0x3 AND reg,8bit/reg	    reg = reg & reg/8bit
0x4 OR  reg,8bit/reg		reg = reg | reg/8bit
0x5 NOT reg					reg = ~reg
0x6 CMP reg, 8bit/reg		Reg get comapred against reg/8bit and sets flags (l,e,z)
0x7 LR reg, 8bit/addr		Loads value or value at memory address into register
0x8 WR 8bit/reg, addr		Writes register or 8bit value to memory
0x9 JMP addr				sets PC to addr
0xa JMF flag, addr			sets PC to addr if inputed flag is set flag number XXXX0YYY YYY = flag code
0xb SUB reg, 8bit/reg		reg = reg - reg/8bit
0xc PUSH 8bit/reg          push the value in a register or an 8bit value onto the stack
0xd POP  reg                pop the first value in the stack and put it in reg
0xe IP reg					Puts input from input device(terminal) into register
0xf OP reg					Outputs register into output device(terminal)



--------MACHINE CODE LAYOUT----------
XXXXYZZZ AAAAAAAA BBBBBBBB

X: 4 bit instruction code
Y: 0 if argument is value, 1 if argument is a register or address if its 8bit/addr (0/1)
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

16bit SP (Stack Pointer)
16bit PC (Program Counter)
8bit IR (Insctruction Register/Current Insctruction)


Flag
[l,e,c,o,z,n,0,0]

l 0x0 LESS
e 0x1 EQUALS
c 0x2 CARRY
o 0x3 OVERFLOW
z 0x4 ZERO
n 0x5 NEGATIVE


-------MEMORY-------------
0x0000-0xb8ef General Storage
0xb8f0-0xdfff Video Memory for 100x100 screen (goning to be implemted soon)
0xe000-0xfffe Instructions
0xffff The stack starts at 0xffff and goes down from there

```