#ifndef IF_ID_H
#define IF_ID_H

#include <systemc.h>

/*
    IF/ID Pipeline Register
    Armazena a instrução buscada da memória de instrução e o valor do PC
    para passar para a próxima fase (ID - decode).
*/

SC_MODULE(IF_ID) {
    // Entradas
    sc_in<bool> clock{"clock"};
    sc_in<bool> enable{"enable"};
    sc_in<bool> reset{"reset"};
    sc_in<sc_int<32>> pc_in{"pc_in"};
    sc_in<sc_int<32>> instruction_in{"instruction_in"};

    // Saídas
    sc_out<sc_int<32>> pc_out{"pc_out"};
    sc_out<sc_int<32>> instruction_out{"instruction_out"};

    void process(){
        if(reset.read()){
            pc_out.write(0);
            instruction_out.write(0);
        }
        else if(enable.read()){
            pc_out.write(pc_in.read());
            instruction_out.write(instruction_in.read());
        }
    }

    SC_CTOR(IF_ID) {
        std::cout << "New component - IF/ID" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif