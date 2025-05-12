#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <systemc.h>

SC_MODULE(ProgramCounter) {
    sc_in_clk clock{"clock"};                      
    sc_in<bool> reset{"reset"};                    
    sc_in<bool> load{"load"};                     
    sc_in<bool> enable{"enable"};                  

    sc_in<sc_uint<8>> pc_in{"pc_in"};            
    sc_out<sc_uint<8>> pc_out{"pc_out"};            

    sc_uint<8> pc_reg;

    void update_pc(){
        if(reset.read()){
            pc_reg = 0;
        }
        else if(load.read()){
            pc_reg = pc_in.read();
        }
        else if(enable.read()){
            pc_reg++;
        }
        pc_out.write(pc_reg);
    }

    SC_CTOR(ProgramCounter){
        std::cout << "New component - Program Counter" << std::endl;
        SC_METHOD(update_pc);
        sensitive << clock.pos();
    }
};

#endif
