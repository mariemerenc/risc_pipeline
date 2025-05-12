#include "systemc.h"
#include "program_counter.h"

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS);

    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<bool> load;
    sc_signal<sc_uint<8>> counterIn;
    sc_signal<sc_uint<8>> counterOut;

    ProgramCounter pc("ProgramCounter");
    pc.clock(clock);
    pc.reset(reset);
    pc.enable(enable);
    pc.load(load);
    pc.pc_in(counterIn);
    pc.pc_out(counterOut);

    sc_trace_file *tf = sc_create_vcd_trace_file("pc_trace");
    tf->set_time_unit(1, SC_NS);
    sc_trace(tf, clock, "clock");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, load, "load");
    sc_trace(tf, counterIn, "pc_in");
    sc_trace(tf, counterOut, "pc_out");

    std::cout << "ProgramCounter testbench starting..." << std::endl;

    reset.write(false);
    enable.write(false);
    load.write(false);
    counterIn.write(0);

    sc_start(10, SC_NS);

    reset.write(true);
    sc_start(10, SC_NS);
    reset.write(false);
    std::cout << "[RESET] pc_out = " << counterOut.read() << std::endl;

    // INCREMENTAR 3 vezes
    enable.write(true);
    for (int i = 0; i < 3; ++i) {
        sc_start(10, SC_NS);
        std::cout << "[INCREMENT " << i+1 << "] pc_out = " << counterOut.read() << std::endl;
    }
    enable.write(false);

    counterIn.write(100);
    load.write(true);
    sc_start(10, SC_NS);
    load.write(false);
    std::cout << "[LOAD 100] pc_out = " << counterOut.read() << std::endl;

    enable.write(true);
    sc_start(10, SC_NS);
    enable.write(false);
    std::cout << "[POST-LOAD INCREMENT] pc_out = " << counterOut.read() << std::endl;

    std::cout << "ProgramCounter testbench completed." << std::endl;
    sc_close_vcd_trace_file(tf);
    return 0;
}
