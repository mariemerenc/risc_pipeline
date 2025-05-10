#include <systemc.h>
#include "alu.h"  

SC_MODULE(alu_tb) {
    sc_signal<sc_int<32>> operand1;
    sc_signal<sc_int<32>> operand2;
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_int<32>> result;
    sc_signal<bool> N;
    sc_signal<bool> Z;
    sc_clock clock;

    ALU* alu_inst;

    void apply_stimulus() {
        operand1.write(10); operand2.write(5); opcode.write(1); wait(10, SC_NS);
        cout << "[ADD] 10 + 5 = " << result.read() << ", Z = " << Z.read() << ", N = " << N.read() << endl;

        operand1.write(10); operand2.write(15); opcode.write(2); wait(10, SC_NS);
        cout << "[SUB] 10 - 15 = " << result.read() << ", Z = " << Z.read() << ", N = " << N.read() << endl;

        operand1.write(0b1100); operand2.write(0b1010); opcode.write(3); wait(10, SC_NS);
        cout << "[AND] 1100 & 1010 = " << result.read() << ", Z = " << Z.read() << ", N = " << N.read() << endl;

        operand1.write(0b1100); operand2.write(0b1010); opcode.write(4); wait(10, SC_NS);
        cout << "[OR] 1100 | 1010 = " << result.read() << ", Z = " << Z.read() << ", N = " << N.read() << endl;

        operand1.write(5); operand2.write(-5); opcode.write(1); wait(10, SC_NS);
        cout << "[ADD] 5 + (-5) = " << result.read() << ", Z = " << Z.read() << ", N = " << N.read() << endl;

        sc_stop(); // End simulation
    }

    SC_CTOR(alu_tb) : clock("clock", 10, SC_NS) {
        alu_inst = new ALU("alu_instance");
        alu_inst->in1(operand1);
        alu_inst->in2(operand2);
        alu_inst->op(opcode);
        alu_inst->out(result);
        alu_inst->N(N);
        alu_inst->Z(Z);

        SC_THREAD(apply_stimulus);
    }

    ~alu_tb() {
        delete alu_inst;
    }
};

int sc_main(int argc, char* argv[]) {
    alu_tb test("alu_testbench");
    sc_start();
    return 0;
}
