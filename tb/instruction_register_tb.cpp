#include <systemc.h>
#include "instruction_register.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_uint<32>> instructionIn;
    sc_signal<sc_uint<32>> instructionOut;
    sc_signal<bool> enable;
    sc_signal<bool> write;
    sc_clock clock("clock", 10, SC_NS);

    InstructionRegister ir("InstructionRegister");
    ir.instructionIn(instructionIn);
    ir.instructionOut(instructionOut);
    ir.enable(enable);
    ir.write(write);
    ir.clock(clock);

    // VCD trace file
    sc_trace_file* tf = sc_create_vcd_trace_file("instruction_register_trace");
    sc_trace(tf, instructionIn, "instructionIn");
    sc_trace(tf, instructionOut, "instructionOut");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, write, "write");
    sc_trace(tf, clock, "clock");

    std::cout << "Running InstructionRegister testbench..." << std::endl;

    // test 1: W on, E on
    enable.write(true);
    write.write(true);
    instructionIn.write(0x12345678);
    sc_start(10, SC_NS);
    std::cout << "[WRITE] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    // Test 2: W off, E on
    write.write(false);
    instructionIn.write(0x87654321); // shouldn't affect output
    sc_start(10, SC_NS);
    std::cout << "[HOLD] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    // Test 3: E off, W on
    enable.write(false);
    write.write(true);
    instructionIn.write(0xDEADBEEF); // should be ignored
    sc_start(10, SC_NS);
    std::cout << "[DISABLED] instructionOut = 0x" << std::hex << instructionOut.read() << std::endl;

    std::cout << "InstructionRegister testbench completed." << std::endl;

    sc_close_vcd_trace_file(tf);
    return 0;
}
