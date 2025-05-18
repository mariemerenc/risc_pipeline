#ifndef DMEM_H
#define DMEM_H

#include <systemc.h>

#define DMEM_SIZE 1024

/*
    * Componente: DMEM
    * Descrição: Memória de dados (DMEM) para armazenamento de dados (1024 posições de 32 bits).
    * 
    * Entradas:
    * - clock: sinal de clock
    * - dmem_enable: habilita a memória (1 = habilitada, 0 = desabilitada)
    * - dmem_write: habilita escrita na memória (1 = escrita, 0 = leitura)
    * - dmem_address: endereço da memória (32 bits)
    * - dmem_dataIn: dado a ser escrito na memória (32 bits)
    * 
    * Saídas:
    * - dmem_dataOut: dado lido da memória (32 bits)
*/

SC_MODULE(DMEM) {
    //entradas
    sc_in<bool> clock{"clock"};             
    sc_in<bool> dmem_enable{"dmem_enable"};           
    sc_in<bool> dmem_write{"dmem_write"};             
    sc_in<sc_int<32>> dmem_address{"dmem_address"};  
    sc_in<sc_int<32>> dmem_dataIn{"dmem_dataIn"};     

    //saída
    sc_out<sc_int<32>> dmem_dataOut{"dmem_dataOut"};  

    //memória de dados
    sc_int<32> memory[DMEM_SIZE];

    // processo principal
    void process() {
        if (dmem_enable.read()) {
            if (dmem_write.read()) {
                // escrita
                memory[dmem_address.read()] = dmem_dataIn.read();
            } else {
                // leitura
                dmem_dataOut.write(memory[dmem_address.read()]);
            }
        }
        else {
            //quando enable é 0, saída deve ser zerada (evita lixo)
            dmem_dataOut.write(0);
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
        if(index >= 0 && index < DMEM_SIZE){
            memory[index] = value;
        }
        else{
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
