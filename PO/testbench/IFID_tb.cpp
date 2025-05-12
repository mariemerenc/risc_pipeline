#include <systemc.h>
#include "IFID.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<32>> pc_in, instruction_in;
    sc_signal<sc_uint<32>> pc_out, instruction_out;

    IFID ifid("IFID");
    ifid.pc_in(pc_in);
    ifid.instruction_in(instruction_in);
    ifid.pc_out(pc_out);
    ifid.instruction_out(instruction_out);

    sc_trace_file *tf = sc_create_vcd_trace_file("ifid_wave");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, instruction_in, "instruction_in");
    sc_trace(tf, pc_out, "pc_out");
    sc_trace(tf, instruction_out, "instruction_out");

    // Estímulos
    pc_in = 0x00000004;
    instruction_in = 0x8C130004; // exemplo de instrução LW
    sc_start(10, SC_NS);

    pc_in = 0x00000008;
    instruction_in = 0x022DA822; // exemplo de instrução SUB
    sc_start(10, SC_NS);

    sc_close_vcd_trace_file(tf);
    return 0;
}
