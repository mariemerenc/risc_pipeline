#ifndef SIGNEXT_H
#define SIGNEXT_H

#include "systemc.h"

SC_MODULE(SignExtend) {
    // Entrada de 32 bits, mas consideraremos apenas os 16 bits menos significativos
    sc_in<sc_uint<32>> in{"in"};

    // Saída com extensão de sinal (signed 32 bits)
    sc_out<sc_int<32>> out{"out"};

    void process() {
        // Pega os 16 bits menos significativos e interpreta como número com sinal
        sc_int<16> imm = static_cast<sc_int<16>>(in.read().range(15, 0));
        // Escreve no registrador de saída com sinal estendido
        out.write(imm);
    }

    SC_CTOR(SignExtend) {
        SC_METHOD(process);
        sensitive << in;
    }
};

#endif // SIGNEXT_H
