#ifndef SHIFT_H
#define SHIFT_H

#include <systemc.h>

/*
    * Componente: Shift
    * Descrição: Desloca um valor de 32 bits para a esquerda ou direita.
    * 
    * Entradas:
    * - shift_in: valor a ser deslocado (32 bits)
    * - shift_amount: quantidade de deslocamento (0-31)
    * - shift_dir: direção do deslocamento (0 = esquerda, 1 = direita)
    * 
    * Saída:
    * - shift_out: resultado do deslocamento (32 bits)
*/

SC_MODULE(Shift) {
    // entradas
    sc_in<sc_int<32>> shift_in{"shift_in"};                 // valor a ser deslocado
    sc_in<sc_int<5>> shift_amount{"shift_amount"}; // quantidade de deslocamento (0–31)
    sc_in<bool> shift_dir{"shift_dir"};          // direção: 0 = esquerda, 1 = direita

    // saída
    sc_out<sc_int<32>> shift_out{"out"};

    // processo de deslocamento
    void process() {
        if(shift_dir.read() == 0){
            shift_out.write(shift_in.read() << shift_amount.read());
        }
        else{
            shift_out.write(shift_in.read() >> shift_amount.read());
        }
    }

    SC_CTOR(Shift) {
        std::cout << "New component - Shift" << std::endl;
        SC_METHOD(process);
        sensitive << shift_in << shift_amount << shift_dir;
    }
};

#endif
