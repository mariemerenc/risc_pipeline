#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

/*
    * Componente: Adder
    * Descrição: Soma dois números de 32 bits.
    * Em geral, usado tanto para incrementar o PC (PC+1 ou PC+4)
    * quanto para calcular endereços de memória (base+offset)
*/

SC_MODULE(Adder) {
    // entradas
    sc_in<sc_uint<32>> a{"a"};
    sc_in<sc_uint<32>> b{"b"};

    // saída
    sc_out<sc_uint<32>> sum{"sum"};

    // processo de soma
    void do_add() {
        sum.write(a.read() + b.read());
    }

    SC_CTOR(Adder) {
        std::cout << "New component - ADDER" << std::endl;
        SC_METHOD(do_add);
        sensitive << a << b;
    }
};

#endif
