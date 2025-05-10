#ifndef MUX2X1_H
#define MUX2X1_H

#include "systemc.h"

 
SC_MODULE(Mux2x1) {
    // Ports
    sc_in<sc_uint<2>> selector;      // Selects input
    sc_in<sc_uint<9>> aluInput;      // Input from ALU
    sc_in<sc_uint<8>> memoryInput;   // Input from data memory
    sc_out<sc_uint<9>> output;       // Output

    // Multiplexing behavior
    void do_select();

    // Constructor
    SC_CTOR(Mux2x1) {
        std::cout << "New component - Mux2x1" << std::endl;
        SC_METHOD(do_select);
        sensitive << selector << aluInput << memoryInput;
    }
};

void Mux2x1::do_select() {
    switch (selector.read()) {
        case 0:
            output.write(aluInput.read());
            break;
        case 1:
            output.write((sc_uint<9>) memoryInput.read());
            break;
        default:
            output.write(0); // Default fallback
    }
}

#endif
