#include "systemc.h"
#include "program_counter.h"

int sc_main(int argc, char* argv[]) {
    // Clock
    sc_clock clock("clock", 10, SC_NS);

    // Signals
    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<bool> load;
    sc_signal<sc_uint<9>> counterIn;
    sc_signal<sc_uint<9>> counterOut;

    // Instantiate Program Counter
    ProgramCounter pc("ProgramCounter");
    pc.clock(clock);
    pc.reset(reset);
    pc.enable(enable);
    pc.load(load);
    pc.counterIn(counterIn);
    pc.counterOut(counterOut);

    // Start testbench
    std::cout << "Running ProgramCounter testbench..." << std::endl;

    // Initialize all control signals
    reset.write(false);
    enable.write(false);
    load.write(false);
    counterIn.write(0);

    // Let initial state settle
    sc_start(10, SC_NS);

    // Test reset
    reset.write(true);
    sc_start(10, SC_NS);
    reset.write(false);
    std::cout << "[RESET] counterOut = " << counterOut.read() << std::endl;

    // Test increment
    enable.write(true);
    for (int i = 0; i < 3; ++i) {
        sc_start(10, SC_NS);
        std::cout << "[INCREMENT] counterOut = " << counterOut.read() << std::endl;
    }
    enable.write(false);

    // Test load
    load.write(true);
    counterIn.write(0x1A3); // Load value 419
    sc_start(10, SC_NS);
    load.write(false);
    std::cout << "[LOAD] counterOut = " << counterOut.read() << std::endl;

    // Continue incrementing after load
    enable.write(true);
    sc_start(10, SC_NS);
    std::cout << "[POST-LOAD INCREMENT] counterOut = " << counterOut.read() << std::endl;
    enable.write(false);

    std::cout << "ProgramCounter testbench completed." << std::endl;
    return 0;
}
