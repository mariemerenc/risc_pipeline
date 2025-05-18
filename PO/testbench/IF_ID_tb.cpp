#include <systemc.h>
#include "IF_ID.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clock;
    sc_signal<bool> enable;
    sc_signal<bool> reset;
    sc_signal<sc_uint<32>> pc_in, instruction_in;
    sc_signal<sc_uint<32>> pc_out, instruction_out;

    IF_ID if_id("IF_ID");
    if_id.clock(clock);
    if_id.enable(enable);
    if_id.reset(reset);
    if_id.pc_in(pc_in);
    if_id.instruction_in(instruction_in);
    if_id.pc_out(pc_out);
    if_id.instruction_out(instruction_out);

    sc_trace_file *tf = sc_create_vcd_trace_file("if_id_wave");
    sc_trace(tf, clock, "clock");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, pc_in, "pc_in");
    sc_trace(tf, instruction_in, "instruction_in");
    sc_trace(tf, pc_out, "pc_out");
    sc_trace(tf, instruction_out, "instruction_out");

    std::cout << "=== Testbench IF/ID starting ===" << std::endl;

    enable = 1;
    reset = 0;
    pc_in = 0;
    instruction_in = 0;

    for (int i = 0; i < 5; ++i) {
        pc_in = 0x1000 + 4 * i;
        instruction_in = 0xA0000000 + i;

        clock = 1; sc_start(1, SC_NS);
        clock = 0; sc_start(1, SC_NS);

        std::cout << "PC: 0x" << std::hex << pc_out.read()
                  << " | Instr: 0x" << instruction_out.read() << std::dec << std::endl;
    }

    reset = 1;
    clock = 1; sc_start(1, SC_NS);
    clock = 0; sc_start(1, SC_NS);
    std::cout << "After reset -> PC: " << pc_out.read() << " | Instr: " << instruction_out.read() << std::endl;

    sc_close_vcd_trace_file(tf);
    std::cout << "=== Testbench IF/ID completed ===" << std::endl;
    return 0;
}
