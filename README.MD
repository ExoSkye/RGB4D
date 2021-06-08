# RGB4D
## About

A 4d esoteric programming language

## Specification

### Instructions

| Colour (RGBA) | Action
| --- | --- |
| Anything with alpha != 255 | End the program
| <b>Directional</b> | |
| (255,127,0,255) | Changes the code execution direction to +X 
| (255,127,127,255) | Changes the code execution direction to -X 
| (255,191,0,255) | Changes the code execution direction to +Y
| (255,191,127,255) | Changes the code execution direction to -Y 
| (255,63,0,255) | Changes the code execution direction to +Z 
| (255,63,127,255) | Changes the code execution direction to -Z 
| (255,255,0,255) | Changes the code execution direction to +W 
| (255,255,127,255) | Changes the code execution direction to -W 
| <b>Maths</b>|  <b>Resultant value stored in A</b> |
| (127,127,0,255) | Add the current cell value to A
| (127,127,31,255) | Subtract current cell value from A
| (127,127,63,255) | Multiple A by current cell value
| (127,127,127,255) | Divide A by current cell value
| (127,127,158,255) | Increment A
| (127,127,191,255) | Decrement A
| <b>Storage</b> | <b>See [storage notes](#storage-notes)</b>|
| (63,127,0,255) | Increment the cell pointer
| (63,127,127,255) | Decrement the cell pointer
| (63,255,0,255) | Store A to current cell
| (63,255,127,255) | Load A from current cell
| (63,255,255,255) | Store a random value into A - From MT19937
| (63,255,63,255) | Reset A 
| <b>Equality</b> | <b>When true direction is set to +X, otherwise direction is set to -X</b>  |
| (191,63,127,255) | Current cell value == A
| (191,127,127,255) | Current cell value > A
| (191,191,127,255) | Current cell value < A
| (191,127,0,255) | Current cell value >= A
| (191,191,0,255) | Current cell value =< A
| (191,255,0,255) | Current cell value != A
| <b>Functions</b> | <b>See [function notes](#function-notes)</b>
| (255,255,255,255) | Run function A
| (0,0,0,255) | Define function A
| (255,0,0,255) | End function definition
| <b>I/O</b> | |
| (255,127,255,255) | Take one character as input and store in A
| (255,0,255,255) | Print ASCII Character for A

#### Storage notes

RGB4D uses a cell based storage system (with a cell pointer and 256 uint16_t cells). It also has an Accumulator (A) which is uint16_t and is used by most instructions which operate on a value

#### Function notes

Functions are specified by a number, which is usually passed as A.
The parameters for a function should be in the cells including and after the cell denoted by the cell pointer.
Functions may also be loaded from an ELF or DLL library (NOTE: This feature isn't required and thus won't be in all interpreters that are made).
If a function is loaded from a library then it is numbered as the function's number in that library but with 10000 (This number isn't meaningful in any way, it's just arbritary) added to it.

### Rules

For storage see [storage notes](#storage-notes)

X, Y and Z are all limited to having a max value of 16.
W is limited by the maximum unsigned byte that the target can support (so for a 64bit CPU it'd be 2^64 whilst for an 8bit CPU it'd be limited to 256)

## This interpreter

This interpreter is written in C++ and is the 'official' interpreter (as in the language creator made it)
