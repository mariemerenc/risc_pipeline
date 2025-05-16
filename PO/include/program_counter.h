#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include <systemc.h>

/*
    * Componente: Program Counter (PC)
    * Descrição: Contador de programa para controle de fluxo de execução.
    * 
    * Entradas:
    * - clock: sinal de clock
    * - pc_reset: sinal de reset (1 = reset, 0 = normal)
    * - pc_load: sinal de load (1 = carrega valor de pc_in, 0 = não carrega)
    * - pc_enable: sinal de enable (1 = incrementa o PC, 0 = não incrementa)
    * - pc_in: valor a ser carregado no PC (32 bits)
    * 
    * Saída:
    * - pc_out: valor atual do PC (32 bits)
*/

SC_MODULE(ProgramCounter) {
    //entradas
    sc_in_clk clock{"clock"};                      
    sc_in<bool> pc_reset{"reset"};                    
    sc_in<bool> pc_load{"load"};                     
    sc_in<bool> pc_enable{"enable"};                  
    sc_in<sc_uint<32>> pc_in{"pc_in"};

    //saída
    sc_out<sc_uint<32>> pc_out{"pc_out"};            

    //registrador interno
    sc_uint<32> pc_reg;

    //processo de atualização do PC
    void update_pc(){
        // Reset: zera o PC
        if(pc_reset.read()){
            pc_reg = 0;
        }
        // Load: carrega o valor de pc_in
        else if(pc_load.read()){
            pc_reg = pc_in.read();
        }
        // Incrementa o PC
        else if(pc_enable.read()){
            pc_reg++;
        }
        // Atualiza a saída
        pc_out.write(pc_reg);
    }

    SC_CTOR(ProgramCounter){
        std::cout << "New component - Program Counter" << std::endl;
        SC_METHOD(update_pc);
        sensitive << clock.pos();
    }
};

#endif
