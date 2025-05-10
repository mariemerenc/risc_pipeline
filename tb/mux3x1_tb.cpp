#include <systemc.h>
#include "mux3x1.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<sc_uint<2>> selector;
    sc_signal<sc_int<32>> aluResult;
    sc_signal<sc_int<32>> dataMemory;
    sc_signal<sc_uint<8>> immediateValue;
    sc_signal<sc_int<32>> output;

    // Instantiate module
    Mux3x1 mux("mux3x1");
    mux.selector(selector);
    mux.aluResult(aluResult);
    mux.dataMemory(dataMemory);
    mux.immediateValue(immediateValue);
    mux.output(output);

    // VCD waveform tracing
    sc_trace_file* tf = sc_create_vcd_trace_file("mux3x1_trace");
    sc_trace(tf, selector, "selector");
    sc_trace(tf, aluResult, "aluResult");
    sc_trace(tf, dataMemory, "dataMemory");
    sc_trace(tf, immediateValue, "immediateValue");
    sc_trace(tf, output, "output");

    std::cout << "Running Mux3x1 testbench...\n";

    // Test Case 0: selector = 0 → aluResult
    aluResult.write(0xDEADBEEF);
    dataMemory.write(0x12345678);
    immediateValue.write(0x42);
    selector.write(0);
    sc_start(1, SC_NS);
    std::cout << "[SELECT 0] output = 0x" << std::hex << output.read() << " (expected 0xDEADBEEF)\n";

    // Test Case 1: selector = 1 → dataMemory
    selector.write(1);
    sc_start(1, SC_NS);
    std::cout << "[SELECT 1] output = 0x" << std::hex << output.read() << " (expected 0x12345678)\n";

    // Test Case 2: selector = 2 → immediateValue (sign-extended)
    selector.write(2);
    immediateValue.write(0xF4);  // = -12 if sign-extended to 32 bits
    sc_start(1, SC_NS);
    std::cout << "[SELECT 2] output = " << std::dec << output.read() << " (expected 244 or -12 if sign-extended)\n";

    // Test Case 3: invalid selector = 3 → default = 0
    selector.write(3);
    sc_start(1, SC_NS);
    std::cout << "[SELECT invalid] output = " << output.read() << " (expected 0)\n";

    sc_close_vcd_trace_file(tf);
    std::cout << "Mux3x1 testbench completed.\n";

    return 0;
}
