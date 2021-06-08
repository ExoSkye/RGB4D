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
| <b>Storage</b> | |
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
| (191,191,127,255

### Rules

## This interpreter
