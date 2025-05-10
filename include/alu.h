#ifndef ALU_H
#define ALU_H

#include <systemc.h>

SC_MODULE(ALU) {
    sc_in<sc_int<32>> in1, in2;
    sc_in<sc_uint<4>> op;
    sc_out<sc_int<32>> out;
    sc_out<bool> Z, N;

    void operate();

    SC_CTOR(ALU);
};

#endif
