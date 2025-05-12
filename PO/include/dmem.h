#ifndef DMEM_H
#define DMEM_H

#include <systemc.h>

#define DMEM_SIZE 1024

SC_MODULE(DMEM) {
    sc_in<bool> clock{"clock"};             
    sc_in<bool> enable{"enable"};           
    sc_in<bool> write{"write"};             
    sc_in<sc_uint<32>> address{"address"};  
    sc_in<sc_int<32>> dataIn{"dataIn"};     

    sc_out<sc_int<32>> dataOut{"dataOut"};  

    sc_int<32> memory[DMEM_SIZE];

    // processo principal
    void process() {
        if (enable.read()) {
            if (write.read()) {
                // escrita
                memory[address.read()] = dataIn.read();
            } else {
                // leitura
                dataOut.write(memory[address.read()]);
            }
        }
        else {
            //quando enable é 0, saída deve ser zerada (evita lixo)
            dataOut.write(0);
        }
    }

    //acesso externo direto à memória (debug)
    sc_int<32> read_memory(int index) {
        if (index >= 0 && index < DMEM_SIZE) {
            return memory[index];
        } else {
            std::cerr << "Erro de leitura: índice fora do intervalo!" << std::endl;
            return 0;
        }
    }

    void write_memory(int index, sc_int<32> value) {
        if (index >= 0 && index < DMEM_SIZE) {
            memory[index] = value;
        } else {
            std::cerr << "Erro de escrita: índice fora do intervalo!" << std::endl;
        }
    }

    SC_CTOR(DMEM) {
        std::cout << "New component - DMEM" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif
