#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include "systemc.h"

 
SC_MODULE(ProgramCounter) {
    // Port declarations
    sc_in_clk clock;                   // Clock input
    sc_in<bool> reset;                 // Reset signal
    sc_in<bool> enable;                // Enable increment
    sc_in<bool> load;                  // Load new value
    sc_in<sc_uint<9>> counterIn;       // Value to load
    sc_out<sc_uint<9>> counterOut;     // Current PC value

    // Internal counter register
    sc_uint<9> count = 0;

    // Process logic
    void updateCounter();

    // Constructor
    SC_CTOR(ProgramCounter) {
        std::cout << "New component - Program Counter" << std::endl;
        SC_METHOD(updateCounter);
        sensitive << reset << clock.pos();
    }
};

void ProgramCounter::updateCounter() {
    if (reset.read() == 1) {
        count = 0;
    } else if (load.read() == 1) {
        count = counterIn.read();
    } else if (enable.read() == 1) {
        count = count + 1;
    }
    counterOut.write(count);
}

#endif
