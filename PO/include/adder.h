#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

SC_MODULE(Adder) {
    // Entradas
    sc_in<sc_uint<32>> a{"a"};
    sc_in<sc_uint<32>> b{"b"};

    // Saída
    sc_out<sc_uint<32>> sum{"sum"};

    // Processo de soma
    void do_add() {
        sum.write(a.read() + b.read());
    }

    SC_CTOR(Adder) {
        std::cout << "New component - ADDER" << std::endl;
        SC_METHOD(do_add);
        sensitive << a << b;
    }
};

#endif // ADDER_H
