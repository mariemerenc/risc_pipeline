#ifndef SIGNEXT_H
#define SIGNEXT_H

#include "systemc.h"

/*
    * Componente: SignExtend
    * Descrição: Extensão de sinal para um valor de 16 bits para 32 bits.
    * 
    * Entradas:
    * - sign_ext_in: valor de entrada (32 bits)
    * 
    * Saída:
    * - sign_ext_out: valor de saída (32 bits, com sinal estendido)
*/

SC_MODULE(SignExtend) {
    // entrada de 32 bits, mas consideraremos apenas os 16 bits menos significativos
    sc_in<sc_uint<32>> sign_ext_in{"sign_ext_in"};

    // saída com extensão de sinal (signed 32 bits)
    sc_out<sc_int<32>> sign_ext_out{"sign_ext_out"};

    void process() {
        // pega os 16 bits menos significativos e interpreta como número com sinal
        sc_int<16> imm = static_cast<sc_int<16>>(sign_ext_in.read().range(15, 0));
        // escreve no registrador de saída com sinal estendido
        sign_ext_out.write(imm);
    }

    SC_CTOR(SignExtend){
        SC_METHOD(process);
        sensitive << sign_ext_in;
    }
};

#endif
