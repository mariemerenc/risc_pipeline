#ifndef SHIFT_H
#define SHIFT_H

#include <systemc.h>

SC_MODULE(Shift) {
    // Entradas
    sc_in<sc_uint<32>> in{"in"};                 // Valor a ser deslocado
    sc_in<sc_uint<5>> shift_amount{"shift_amount"}; // Quantidade de deslocamento (0–31)
    sc_in<bool> shift_dir{"shift_dir"};          // Direção: 0 = esquerda, 1 = direita

    // Saída
    sc_out<sc_uint<32>> out{"out"};

    void process() {
        if (shift_dir.read() == 0) {
            out.write(in.read() << shift_amount.read());
        } else {
            out.write(in.read() >> shift_amount.read());
        }
    }

    SC_CTOR(Shift) {
        std::cout << "New component - SHIFT" << std::endl;
        SC_METHOD(process);
        sensitive << in << shift_amount << shift_dir;
    }
};

#endif // SHIFT_H
