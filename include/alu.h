#ifndef ALU_H
#define ALU_H

#include <systemc.h>

SC_MODULE(ALU) {
    sc_in<sc_int<32>> in1{"in1"}, in2{"in2"};
    sc_in<sc_uint<4>> op{"op"};
    sc_out<sc_int<32>> out{"out"};
    sc_out<bool> Z{"Z"}, N{"N"};

    void operate();

    SC_CTOR(ALU);
};

#endif
