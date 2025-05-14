#include <systemc.h>
#include "alu.h"

/*
    Testbench para a ALU (Unidade Lógica Aritmética)
    Testa operações lógicas e aritméticas.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "alu_waves.vcd".
    O testbench executa as seguintes operações:
        1. AND
        2. OR
        3. XOR
        4. NOT (in1)
        5. ADD
        6. SUB
        7. CMP (com sinal)
        8. CMP (negativo)
        9. CMP (zero)
*/

SC_MODULE(alu_tb) {
    sc_signal<sc_int<32>> operand1, operand2;
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_int<32>> result;
    sc_signal<bool>       N, Z;

    ALU* alu_inst;
    sc_trace_file* tf;

    void apply_stimulus() {
        tf = sc_create_vcd_trace_file("alu_waves");
        tf->set_time_unit(1, SC_NS);
        sc_trace(tf, operand1, "operand1");
        sc_trace(tf, operand2, "operand2");
        sc_trace(tf, opcode,   "opcode");
        sc_trace(tf, result,   "result");
        sc_trace(tf, N,        "flag_N");
        sc_trace(tf, Z,        "flag_Z");

        cout << "ALU testbench starting..." << endl;

        #define TEST(name, a, b, op)                              \
            operand1.write(a); operand2.write(b); opcode.write(op); \
            wait(1, SC_NS);                                        \
            cout << "[" name "] "                                 \
                 << (a) << "," << (b)                             \
                 << " -> res=" << result.read()                   \
                 << " Z=" << Z.read() << " N=" << N.read() << endl;

        // according to alu.cpp mapping:
        // 1: AND, 2: OR, 3: XOR, 4: NOT (in1), 
        // 5: ADD, 6: SUB, 7: CMP

        TEST("AND",  0b1100, 0b1010, 1);
        TEST("OR",   0b1100, 0b1010, 2);
        TEST("XOR",  0b1100, 0b1010, 3);
        TEST("NOT",  0b0011, 0,           4);
        TEST("ADD",  10,    5,           5);
        TEST("SUB",  10,   15,           6);
        TEST("CMP (pos)", 7,  7,         7);
        TEST("CMP (neg)", 5, 10,         7);
        TEST("CMP (zero)", 3, 3,         7);

        #undef TEST

        sc_close_vcd_trace_file(tf);
        cout << "ALU testbench completed." << endl;
        sc_stop();
    }

    SC_CTOR(alu_tb) {
        alu_inst = new ALU("alu_instance");
        alu_inst->alu_in1(   operand1);
        alu_inst->alu_in2(   operand2);
        alu_inst->alu_op(    opcode);
        alu_inst->alu_out(   result);
        alu_inst->alu_N(     N);
        alu_inst->alu_Z(     Z);

        SC_THREAD(apply_stimulus);
    }

    ~alu_tb() { delete alu_inst; }
};

int sc_main(int argc, char* argv[]) {
    alu_tb tb("alu_testbench");
    sc_start(); 
    return 0;
}
