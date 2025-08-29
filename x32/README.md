# xarch-origin-x32

## Instruction entry

|  Field   | Bits size | Description                                                                                                                    |
| :------: | :-------: | :----------------------------------------------------------------------------------------------------------------------------- |
| `opcode` |    12     | Opcode of the instruction, long 9 bits, where the 3 least significant bits identify operand type (0 = register, 1 = immediate) |
|  `des`   |    32     | Destination                                                                                                                    |
|  `op_a`  |    32     | Operand A                                                                                                                      |
|  `op_b`  |    32     | Operand B                                                                                                                      |

