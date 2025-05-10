#ifndef MUX3X1_H
#define MUX3X1_H

#include "systemc.h"

 
SC_MODULE(Mux3x1) {
    // Ports
    sc_in<sc_uint<2>> selector;        // Selects input
    sc_in<sc_int<32>> aluResult;       // Input from ALU
    sc_in<sc_int<32>> dataMemory;      // Input from Data Memory
    sc_in<sc_uint<8>> immediateValue;  // Immediate value
    sc_out<sc_int<32>> output;         // Output

    // Multiplexing behavior
    void do_select();

    // Constructor
    SC_CTOR(Mux3x1) {
        std::cout << "New component - Mux3x1" << std::endl;
        SC_METHOD(do_select);
        sensitive << selector << aluResult << dataMemory << immediateValue;
    }
};

void Mux3x1::do_select() {
    switch (selector.read()) {
        case 0:
            output.write(aluResult.read());
            break;
        case 1:
            output.write(dataMemory.read());
            break;
        case 2:
            output.write((sc_int<32>) immediateValue.read());
            break;
        default:
            output.write(0); // Default fallback
    }
}

#endif
