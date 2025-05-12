#include <systemc.h>
#include "mux2x1.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<sc_uint<32>> in0, in1, out;
    sc_signal<bool> sel;

    // Mux instance
    Mux2x1 mux("MUX");
    mux.in0(in0);
    mux.in1(in1);
    mux.sel(sel);
    mux.out(out);

    // VCD dump
    sc_trace_file *wf = sc_create_vcd_trace_file("mux_wave");
    sc_trace(wf, in0, "in0");
    sc_trace(wf, in1, "in1");
    sc_trace(wf, sel, "sel");
    sc_trace(wf, out, "out");

    std::cout << "Mux 2x1 testbench starting..." << std::endl;

    // Test
    in0 = 10;
    in1 = 20;

    sel = 0;
    sc_start(1, SC_NS);
    std::cout << "sel = 0 -> out = " << out.read() << std::endl;

    sel = 1;
    sc_start(1, SC_NS);
    std::cout << "sel = 1 -> out = " << out.read() << std::endl;

    std::cout << "Mux 2x1 testbench completed." << std::endl;
    sc_close_vcd_trace_file(wf);
    return 0;
}
