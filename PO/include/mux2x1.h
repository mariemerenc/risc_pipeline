#ifndef MUX2X1_H
#define MUX2X1_H

#include <systemc.h>

SC_MODULE(Mux2x1) {
    sc_in<sc_uint<32>> in0{"in0"};
    sc_in<sc_uint<32>> in1{"in1"};
    sc_in<bool> sel{"sel"};
    sc_out<sc_uint<32>> out{"out"};

    void do_mux() {
        if (sel.read() == 0) {
            out.write(in0.read());
        } else {
            out.write(in1.read());
        }
    }

    SC_CTOR(Mux2x1) {
        SC_METHOD(do_mux);
        sensitive << in0 << in1 << sel;
    }
};

#endif
