#include "alu.h"
#include <iostream>

void ALU::operate() {
    sc_int<32> a = in1.read();
    sc_int<32> b = in2.read();
    sc_int<32> res = 0;

    // Opcode mapping (4 bits):
    // 0x0: NOP
    // 0x1: AND
    // 0x2: OR
    // 0x3: XOR
    // 0x4: NOT (in1 only)
    // 0x5: ADD
    // 0x6: SUB
    // 0x7: CMP (flags only; res = 0)

    switch (op.read()) {
        case 0x0:  // NOP
            res = 0;
            break;
        case 0x1:  // AND
            res = a & b;
            break;
        case 0x2:  // OR
            res = a | b;
            break;
        case 0x3:  // XOR
            res = a ^ b;
            break;
        case 0x4:  // NOT
            res = ~a;
            break;
        case 0x5:  // ADD
            res = a + b;
            break;
        case 0x6:  // SUB
            res = a - b;
            break;
        case 0x7:  // CMP: subtract for flags, result not written to a register
            res = 0;  // we do not write result back
            break;
        default:
            std::cerr << "[ALU] Invalid opcode: 0x"
                      << std::hex << op.read() << std::dec << std::endl;
            res = 0;
            break;
    }


    // flags Z e N vêm do resultado da operação,
    // exceto para CMP, onde é a subtração (a - b)
    sc_int<32> cmp_val = (op.read() == 7) ? sc_int<32>(a - b) : res;

    out.write(res);
    Z.write(cmp_val == 0);
    N.write(cmp_val < 0);
}

SC_HAS_PROCESS(ALU);

ALU::ALU(sc_module_name name) : sc_module(name) {
    std::cout << "New component - ALU" << std::endl;
    SC_METHOD(operate);
    sensitive << in1 << in2 << op;
}
