#ifndef IFID_H
#define IFID_H

#include "systemc.h"

SC_MODULE(IFID) {
    sc_in<sc_uint<32>> pc_in, instruction_in;
    sc_out<sc_uint<32>> pc_out, instruction_out;

    void process() {
        pc_out.write(pc_in.read());
        instruction_out.write(instruction_in.read());
    }

    SC_CTOR(IFID) {
        SC_METHOD(process);
        sensitive << pc_in << instruction_in;
    }
};

#endif
