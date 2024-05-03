# 8-Bit Computer
Custom 8-Bit computer emulator enspired by the 6502 written in C++.

# Machine Description

8-bit Data width
16-bit address bus (64 KB)
7 General purpose registers
16 Instructions
1 Flag register with 5 diffrent flags
I/O for program communication using terminal









```
------Instructions---------
0x0 
0x1 ADD reg,8bit/reg      reg = reg + reg/8bit
0x2 ADC reg,8bit/reg      reg = reg + reg/8bit + c
0x3 AND reg,8bit/reg      reg = reg & reg/8bit
0x4 OR  reg,8bit/reg      reg = reg | reg/8bit
0x5 NOT reg               reg = ~reg
0x6 CMP reg, 8bit/reg     Reg get comapred against reg/8bit and sets flags (l,e,z)
0x7 LR reg, 8bit/addr     Loads value or value at memory address into register
0x8 WR 8bit/reg, addr     Writes register or 8bit value to memory
0x9 JMP addr              sets PC to addr
0xa JMF flag, addr        sets PC to addr if inputed flag is set flag number XXXX0YYY YYY = flag code
0xb SUB reg, 8bit/reg     reg = reg - reg/8bit
0xc PUSH 8bit/reg         push the value in a register or an 8bit value onto the stack
0xd POP  reg              pop the top value in the stack and put it in reg
0xe IP reg                Puts input from input device(terminal) into register
0xf OP string/reg         Outputs register or string into output device(terminal)

```

Machine code layout

```
XXXXYZZZ AAAAAAAA BBBBBBBB

X: 4 bit instruction code
Y: 0 for first paramter and 1 for second paramater eg 8bit/reg 8bit value = 0, reg = 1
Z: Register/Flag
A: Second paramter register, value or first byte of 16bit address
B: Second byte of 16bit address
```

Registers
```
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

```
Flags
```
[l,e,c,o,z,0,0,0]

l 0x0 LESS
e 0x1 EQUALS
c 0x2 CARRY
o 0x3 OVERFLOW
z 0x4 ZERO
```


Memory layout

```
0x0000-0xdfff General Storage
0xe000-0xfffe Instructions
0xffff The stack starts at 0xffff and goes down from there
```

