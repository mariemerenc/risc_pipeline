#include "systemc.h"
#include "instruction_register.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_signal<sc_uint<64>> instructionIn;
    sc_signal<sc_uint<64>> instructionOut;
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_clock clock("clock", 10, SC_NS);

    // Instantiate the module
    InstructionRegister ir("InstructionRegister");
    ir.instructionIn(instructionIn);
    ir.instructionOut(instructionOut);
    ir.enable(enable);
    ir.write(write);
    ir.clock(clock);

    // Open VCD trace file
    sc_trace_file* tf = sc_create_vcd_trace_file("instruction_register_trace");
    sc_trace(tf, instructionIn, "instructionIn");
    sc_trace(tf, instructionOut, "instructionOut");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, write, "write");
    sc_trace(tf, clock, "clock");

    std::cout << "Running InstructionRegister testbench..." << std::endl;

    // Simulation
    enable.write(false);
    write.write(false);
    instructionIn.write(0xAAAAAAAAAAAAAAAA);
    sc_start(10, SC_NS);  // 1st rising edge

    enable.write(true);
    write.write(true);
    instructionIn.write(0x1234567890ABCDEF);
    sc_start(10, SC_NS);  // 2nd rising edge (write active)

    std::cout << "[WRITE] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    write.write(false);
    instructionIn.write(0xFFFFFFFFFFFFFFFF);  // Should be ignored
    sc_start(10, SC_NS);  // 3rd rising edge (hold)

    std::cout << "[HOLD] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    enable.write(false);  // Disabled
    instructionIn.write(0x1111111111111111);
    write.write(true);
    sc_start(10, SC_NS);  // 4th rising edge (disabled)

    std::cout << "[DISABLED] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    std::cout << "InstructionRegister testbench completed." << std::endl;

    sc_close_vcd_trace_file(tf);
    return 0;
}
