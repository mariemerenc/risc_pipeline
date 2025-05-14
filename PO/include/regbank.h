#ifndef REGBANK_H
#define REGBANK_H

#include <systemc.h>

/*
    * Componente: RegBank
    * Descrição: Banco de registradores (32 registradores de 32 bits).
    * 
    * Entradas:
    * - clock: sinal de clock
    * - regbank_enable: habilita o banco de registradores (1 = habilitado, 0 = desabilitado)
    * - regbank_write: habilita escrita no banco de registradores (1 = escrita, 0 = leitura)
    * - read_address1: endereço do primeiro registrador a ser lido (5 bits)
    * - read_address2: endereço do segundo registrador a ser lido (5 bits)
    * - write_address: endereço do registrador a ser escrito (5 bits)
    * - write_data: dado a ser escrito no registrador (32 bits)
    * 
    * Saídas:
    * - read_data1: dado lido do primeiro registrador (32 bits)
    * - read_data2: dado lido do segundo registrador (32 bits)
*/

SC_MODULE(RegBank){
    //inputs
    sc_in<bool> clock{"clock"};
    sc_in<bool> regbank_enable{"regbankenable"};
    sc_in<bool> regbank_write{"regbank_write"};
    sc_in<sc_uint<5>> read_address1{"read_address1"}; 
    sc_in<sc_uint<5>> read_address2{"read_address2"}; 
    sc_in<sc_uint<5>> write_address{"write_address"}; 
    sc_in<sc_int<32>> write_data{"write_data"}; 

    //outputs
    sc_out<sc_int<32>> read_data1{"read_data1"};
    sc_out<sc_int<32>> read_data2{"read_data2"}; 
    //regs internos
    sc_signal<sc_int<32>> regs[32];
    

    void write_process(){
        if(regbank_enable.read()){
            if(regbank_write.read()){
                // escrita no registrador de destino
                regs[write_address.read()] = write_data.read();
            }
        }
    }

    void read(){
        if(regbank_enable.read()){
            // leitura dos registradores fonte
            read_data1.write(regs[read_address1.read()]);
            read_data2.write(regs[read_address2.read()]);
        }
    }

    SC_CTOR(RegBank){
        std::cout << "New component - RegBank" << std::endl;
        SC_METHOD(write_process);
        sensitive << clock.pos();
        SC_METHOD(read);
        sensitive << clock.pos();
    }
};

#endif