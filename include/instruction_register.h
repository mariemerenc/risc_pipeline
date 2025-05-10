#ifndef INSTRUCTION_REGISTER_H
#define INSTRUCTION_REGISTER_H

#include "systemc.h"

 
SC_MODULE(InstructionRegister) {
    // Ports
    sc_in<sc_uint<64>> instructionIn;  // Input instruction
    sc_in<bool> enable;                // Enable signal
    sc_in<bool> write;                 // Write control (1: write, 0: hold)
    sc_in<bool> clock;                 // Clock signal
    sc_out<sc_uint<64>> instructionOut; // Output instruction

    // Internal storage
    sc_uint<64> instruction;

    // Behavior method
    void operate();

    // Constructor
    SC_HAS_PROCESS(InstructionRegister);
    InstructionRegister(sc_module_name name) : sc_module(name) {
        std::cout << "New component - Instruction Register" << std::endl;
        SC_METHOD(operate);
        sensitive << clock.pos();
    }
};

void InstructionRegister::operate() {
    if (enable.read()) {
        if (write.read()) {
            instruction = instructionIn.read();
            instructionOut.write(instruction);
        } else {
            instructionOut.write(instruction); // hold current value
        }
    }
}

#endif
