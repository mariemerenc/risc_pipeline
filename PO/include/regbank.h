#ifndef REGBANK_H
#define REGBANK_H

#include <systemc.h>

SC_MODULE(RegBank){
    //inputs
    sc_in<bool> clock{"clock"};
    sc_in<bool> enable{"enable"};
    sc_in<bool> write{"write"};
    sc_in<sc_uint<5>> addressSource1{"addressSource1"};
    sc_in<sc_uint<5>> addressSource2{"addressSource2"};
    sc_in<sc_uint<5>> addressDest{"addressDest"};
    sc_in<sc_int<32>> dataToWrite{"dataToWrite"};
    //outputs
    sc_out<sc_int<32>> dataSource1{"dataSource1"};
    sc_out<sc_int<32>> dataSource2{"dataSource2"};
    //regs internos
    sc_signal<sc_int<32>> regs[32];
    

    void write_process(){
        if (enable.read()) {
            if(write.read()){
                // escrita no registrador de destino
                regs[addressDest.read()] = dataToWrite.read();
            }
        }
    }

    void read(){
        if (enable.read()) {
            // leitura dos registradores fonte
            dataSource1.write(regs[addressSource1.read()]);
            dataSource2.write(regs[addressSource2.read()]);
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