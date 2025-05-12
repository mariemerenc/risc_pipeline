#include <systemc.h>
#include "control_unit.h"

int sc_main(int argc, char* argv[]) {
    // Sinais de entrada e saída
    sc_signal<sc_uint<6>> opcode;
    sc_signal<sc_uint<3>> aluOp;
    sc_signal<bool> aluSrc, regDst, regWrite, memRead, memWrite, memToReg, branch;

    // Instanciação do módulo de controle
    ControlUnit control("control_unit");
    control.opcode(opcode);
    control.aluOp(aluOp);
    control.aluSrc(aluSrc);
    control.regDst(regDst);
    control.regWrite(regWrite);
    control.memRead(memRead);
    control.memWrite(memWrite);
    control.memToReg(memToReg);
    control.branch(branch);

    // Geração de arquivo VCD
    sc_trace_file* tf = sc_create_vcd_trace_file("control_unit_tb");
    tf->set_time_unit(1, SC_NS);

    // Traçar sinais
    sc_trace(tf, opcode, "opcode");
    sc_trace(tf, aluOp, "aluOp");
    sc_trace(tf, aluSrc, "aluSrc");
    sc_trace(tf, regDst, "regDst");
    sc_trace(tf, regWrite, "regWrite");
    sc_trace(tf, memRead, "memRead");
    sc_trace(tf, memWrite, "memWrite");
    sc_trace(tf, memToReg, "memToReg");
    sc_trace(tf, branch, "branch");

    // Teste das instruções
    sc_start(5, SC_NS); opcode.write(0x01); sc_start(5, SC_NS); // AND
    opcode.write(0x13); sc_start(5, SC_NS); // OR
    opcode.write(0x24); sc_start(5, SC_NS); // XOR
    opcode.write(0x36); sc_start(5, SC_NS); // NOT
    opcode.write(0x45); sc_start(5, SC_NS); // CMP
    opcode.write(0x50); sc_start(5, SC_NS); // ADD
    opcode.write(0x57); sc_start(5, SC_NS); // ADDI
    opcode.write(0x61); sc_start(5, SC_NS); // SUB
    opcode.write(0x70); sc_start(5, SC_NS); // LW
    opcode.write(0x80); sc_start(5, SC_NS); // SW
    opcode.write(0x90); sc_start(5, SC_NS); // J
    opcode.write(0xA0); sc_start(5, SC_NS); // BNE
    opcode.write(0xB0); sc_start(5, SC_NS); // BEQ
    opcode.write(0x3F); sc_start(5, SC_NS); // Instrução inválida

    sc_close_vcd_trace_file(tf);
    return 0;
}
