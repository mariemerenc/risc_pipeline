#ifndef INSTRUCTION_REGISTER_H
#define INSTRUCTION_REGISTER_H

#include "systemc.h"

 
SC_MODULE(InstructionRegister) {
    sc_in<sc_uint<32>> instructionIn{"instructionIn"};  
    sc_in<bool> enable{"enable"};                
    sc_in<bool> write{"write"};                 
    sc_in<bool> clock{"clock"};                 
    sc_out<sc_uint<32>> instructionOut{"instructionOut"}; 

    sc_uint<32> instruction;

    void operate();

    SC_HAS_PROCESS(InstructionRegister);
    InstructionRegister(sc_module_name name) : sc_module(name) {
        std::cout << "New component - Instruction Register" << std::endl;
        SC_METHOD(operate);
        sensitive << clock.pos();
    }
};

void InstructionRegister::operate(){
    if(enable.read()){
        if(write.read()){
            instruction = instructionIn.read();
            instructionOut.write(instruction);
        }
        else{
            instructionOut.write(instruction); 
        }
    }
}

#endif
