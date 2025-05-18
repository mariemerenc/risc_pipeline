#ifndef MUX2X1_H
#define MUX2X1_H

#include <systemc.h>

/*
    * Componente: Mux2x1
    * Descrição: Multiplexor 2x1 para selecionar entre dois sinais de entrada.
    * 
    * Entradas:
    * - mux_in1: primeiro sinal de entrada (32 bits)
    * - mux_in2: segundo sinal de entrada (32 bits)
    * - mux_sel: sinal de seleção (0 ou 1)
    * 
    * Saída:
    * - mux_out: sinal de saída (32 bits)
*/

SC_MODULE(Mux2x1) {
    //entrada
    sc_in<sc_int<32>> mux_in1{"in1"};
    sc_in<sc_int<32>> mux_in2{"in2"};
    sc_in<bool> mux_sel{"sel"};

    //saída
    sc_out<sc_int<32>> mux_out{"out"};

    void do_mux() {
        if(mux_sel.read() == 0){
            mux_out.write(mux_in1.read());
        }
        else{
            mux_out.write(mux_in2.read());
        }
    }

    SC_CTOR(Mux2x1) {
        std::cout << "New component - MUX 2x1" << std::endl;
        SC_METHOD(do_mux);
        sensitive << mux_in1 << mux_in2 << mux_sel;
    }
};

#endif
