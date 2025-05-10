#include "alu.h"
#include <iostream>

void ALU::operate() {
    sc_int<32> a = in1.read();
    sc_int<32> b = in2.read();
    sc_int<32> res = 0;

    switch(op.read()) {
        case 0: res = 0; break;             // NOP
        case 1: res = a + b; break;         // ADD
        case 2: res = a - b; break;         // SUB
        case 3: res = a & b; break;         // AND
        case 4: res = a | b; break;         // OR
        case 5: res = a ^ b; break;         // XOR
        case 6: res = (a < b) ? 1 : 0; break; // SLT
        default:
            std::cerr << "[ALU] Invalid opcode: " << op.read() << std::endl;
            res = 0;
            break;
    }

    out.write(res);
    Z.write(res == 0);
    N.write(res < 0);
}

SC_HAS_PROCESS(ALU);

ALU::ALU(sc_module_name name) : sc_module(name) {
    std::cout << "New component - ALU" << std::endl;
    SC_METHOD(operate);
    sensitive << in1 << in2 << op;
}
