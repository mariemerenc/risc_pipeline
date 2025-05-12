#ifndef IMEM_H
#define IMEM_H

#include <systemc.h>

#define IMEM_SIZE 32 

SC_MODULE(IMEM){
    sc_in<bool> clock{"clock"};
    sc_in<bool> enable{"enable"};
    sc_in<bool> write{"write"};
    sc_in<sc_uint<32>> address{"address"};
    sc_out<sc_uint<32>> instruction{"instruction"};

    sc_uint<32> imem[IMEM_SIZE];

    void process(){
        instruction.write(imem[address.read()]);
    }

    SC_CTOR(IMEM){
        std::cout << "New component - IMEM" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif