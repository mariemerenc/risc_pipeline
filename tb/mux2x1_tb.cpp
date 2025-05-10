#include <systemc.h>
#include "mux2x1.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<2>> selector;
    sc_signal<sc_uint<9>> aluInput;
    sc_signal<sc_uint<8>> memoryInput;
    sc_signal<sc_uint<9>> output;

    // Instantiate the module
    Mux2x1 mux("mux2x1");
    mux.selector(selector);
    mux.aluInput(aluInput);
    mux.memoryInput(memoryInput);
    mux.output(output);

    // Monitor output changes
    sc_trace_file* tf = sc_create_vcd_trace_file("mux2x1_trace");
    sc_trace(tf, selector, "selector");
    sc_trace(tf, aluInput, "aluInput");
    sc_trace(tf, memoryInput, "memoryInput");
    sc_trace(tf, output, "output");

    std::cout << "Running Mux2x1 testbench..." << std::endl;

    // Test Case 1: selector = 0 -> output = aluInput
    aluInput.write(0x123);
    memoryInput.write(0x7F);
    selector.write(0);
    sc_start(1, SC_NS);
    std::cout << "[SELECT 0] output = " << output.read() << " (expected 0x123)" << std::endl;

    // Test Case 2: selector = 1 -> output = memoryInput zero-extended
    aluInput.write(0x0);
    memoryInput.write(0xAA);
    selector.write(1);
    sc_start(1, SC_NS);
    std::cout << "[SELECT 1] output = " << output.read() << " (expected 0x0AA)" << std::endl;

    // Test Case 3: selector = 2 (invalid) -> output = 0
    aluInput.write(0x111);
    memoryInput.write(0x22);
    selector.write(2);
    sc_start(1, SC_NS);
    std::cout << "[SELECT invalid] output = " << output.read() << " (expected 0x000)" << std::endl;

    sc_close_vcd_trace_file(tf);
    std::cout << "Mux2x1 testbench completed." << std::endl;

    return 0;
}
