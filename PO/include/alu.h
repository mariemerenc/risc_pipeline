#ifndef ALU_H
#define ALU_H

#include <systemc.h>

/*
    * Componente: ALU
    * Descrição: Unidade Lógica Aritmética (ALU) para operações aritméticas e lógicas.
    * 
    * Entradas:
    * - alu_in1: primeiro operando (32 bits)
    * - alu_in2: segundo operando (32 bits)
    * - alu_op: operação a ser realizada (4 bits)
    * 
    * Saídas:
    * - alu_out: resultado da operação (32 bits)
    * - alu_Z: flag de zero (1 se resultado == 0)
    * - alu_N: flag de negativo (1 se resultado < 0)

    * Executa operações: AND, OR, XOR, NOT, ADD, SUB, CMP (gera flags), possivelmente shifts.
    * Gera sinais de flag Z (zero) e N (negativo) para saltos condicionais.

*/

SC_MODULE(ALU) {
    sc_in<sc_int<32>> alu_in1{"alu_in1"}, alu_in2{"alu_in2"};
    sc_in<sc_uint<4>> alu_op{"alu_op"};
    sc_out<sc_int<32>> alu_out{"alu_out"};
    sc_out<bool> alu_Z{"alu_Z"}, alu_N{"alu_N"};

    void operate();

    SC_CTOR(ALU);
};


void ALU::operate() {
    sc_int<32> a = alu_in1.read();
    sc_int<32> b = alu_in2.read();
    sc_int<32> res = 0;

    // mapeamento de opcode (4 bits):
    // 0x0: NOP
    // 0x1: AND
    // 0x2: OR
    // 0x3: XOR
    // 0x4: NOT (apenas alu_in1)
    // 0x5: ADD
    // 0x6: SUB
    // 0x7: CMP (apenas flags; res = 0)

    switch (alu_op.read()) {
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
        case 0x7:  // CMP
            res = 0; 
            break;
        default:
            std::cerr << "[ALU] Invalid opcode: 0x"
                      << std::hex << alu_op.read() << std::dec << std::endl;
            res = 0;
            break;
    }


    // flags Z e N vêm do resultado da operação,
    // exceto para CMP, onde é a subtração (a - b)
    sc_int<32> cmp_val = (alu_op.read() == 7) ? sc_int<32>(a - b) : res;

    alu_out.write(res);
    alu_Z.write(cmp_val == 0);
    alu_N.write(cmp_val < 0);
}

SC_HAS_PROCESS(ALU);

ALU::ALU(sc_module_name name) : sc_module(name) {
    std::cout << "New component - ALU" << std::endl;
    SC_METHOD(operate);
    sensitive << alu_in1 << alu_in2 << alu_op;
}

#endif
