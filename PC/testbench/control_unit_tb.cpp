#include <systemc.h>
#include "control_unit.h"


/*
    Testbench para o módulo ControlUnit.
    
    Testa a unidade de controle do processador.
    Gera um arquivo VCD para visualização de waveforms.
    O arquivo VCD é gerado com o nome "control_unit_tb.vcd".
    O testbench executa os seguintes testes:
        1. Testa todas as instruções com opcode de 4 bits.
        2. Imprime os sinais de controle gerados.
*/

void print_ctrl(sc_uint<4> opc,
                bool rw, bool mr, bool mw,
                bool aS, bool mTR, bool rd,
                bool br, bool jp,
                sc_uint<4> aO) {
    cout << "OP=" << opc
         << " | regWrite=" << rw
         << " memRead="  << mr
         << " memWrite=" << mw
         << " aluSrc="   << aS
         << " memToReg=" << mTR
         << " regDst="   << rd
         << " branch="   << br
         << " jump="     << jp
         << " aluOp="    << aO
         << endl;
}

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<4>> opcode;
    sc_signal<bool> flagN, flagZ;
    sc_signal<bool> regWrite, memRead, memWrite, aluSrc, memToReg, regDst, branch, jump;
    sc_signal<sc_uint<4>> aluOp;

    ControlUnit cu("CU");
    cu.opcode(opcode);
    cu.flagN(flagN);
    cu.flagZ(flagZ);
    cu.regWrite(regWrite);
    cu.memRead(memRead);
    cu.memWrite(memWrite);
    cu.aluSrc(aluSrc);
    cu.memToReg(memToReg);
    cu.regDst(regDst);
    cu.branch(branch);
    cu.jump(jump);
    cu.aluOp(aluOp);

    // Trace
    sc_trace_file* tf = sc_create_vcd_trace_file("control_unit_tb");
    sc_trace(tf, opcode,   "opcode");
    sc_trace(tf, flagN,    "flagN");
    sc_trace(tf, flagZ,    "flagZ");
    sc_trace(tf, regWrite, "regWrite");
    sc_trace(tf, memRead,  "memRead");
    sc_trace(tf, memWrite, "memWrite");
    sc_trace(tf, aluSrc,   "aluSrc");
    sc_trace(tf, memToReg, "memToReg");
    sc_trace(tf, regDst,   "regDst");
    sc_trace(tf, branch,   "branch");
    sc_trace(tf, jump,     "jump");
    sc_trace(tf, aluOp,    "aluOp");

    cout << "Control Unit testbench starting..." << endl;
    const sc_uint<4> tests[] = {
        OP_AND, OP_OR, OP_XOR, OP_NOT,
        OP_CMP, OP_ADD, OP_SUB,
        OP_LD, OP_ST, OP_J, OP_JN, OP_JZ, 0xF
    };

    for (auto code : tests) {
        // testar flags nas instruções condicionais
        flagN.write(true);
        flagZ.write(true);
        opcode.write(code);
        sc_start(1, SC_NS);
        print_ctrl(code, regWrite.read(), memRead.read(), memWrite.read(),
                   aluSrc.read(), memToReg.read(), regDst.read(),
                   branch.read(), jump.read(), aluOp.read());
    }

    sc_close_vcd_trace_file(tf);
    cout << "Control Unit testbench completed." << endl;
    return 0;
}
