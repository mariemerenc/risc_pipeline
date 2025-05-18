#ifndef IMEM_H
#define IMEM_H

#include <systemc.h>

#define IMEM_SIZE 32

/*
    * Componente: IMEM
    * Descrição: Memória de instruções (IMEM) para armazenamento de instruções (32 posições de 32 bits).
    * 
    * Entradas:
    * - clock: sinal de clock
    * - imem_enable: habilita a memória (1 = habilitada, 0 = desabilitada)
    * - imem_write: habilita escrita na memória (1 = escrita, 0 = leitura)
    * - imem_address: endereço da memória (32 bits)
    * 
    * Saídas:
    * - imem_instruction: instrução lida da memória (32 bits)
*/

SC_MODULE(IMEM){
    //entradas
    sc_in<bool> clock{"clock"};
    sc_in<bool> imem_enable{"enable"};
    sc_in<bool> imem_write{"write"};
    sc_in<sc_uint<32>> imem_address{"address"};

    //saída
    sc_out<sc_uint<32>> imem_instruction{"instruction"};

    //memória de instruções
    sc_uint<32> imem[IMEM_SIZE];

    //processo principal
    void process(){
    if (imem_enable.read()) {
        if(imem_write.read()){
            imem[imem_address.read()] = imem_instruction.read();  // Escrita
        }
        else{
            imem_instruction.write(imem[imem_address.read()]);    // Leitura
        }
    }
    else{
        imem_instruction.write(0); // Sem acesso, saída zerada
    }
}


    SC_CTOR(IMEM){
        std::cout << "New component - IMEM" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif
