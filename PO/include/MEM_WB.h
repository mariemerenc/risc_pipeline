#ifndef MEM_WB_H
#define MEM_WB_H

#include <systemc.h>

SC_MODULE(MEM_WB) {
    sc_in<bool> clock{"clock"};
    sc_in<bool> reset{"reset"};
    sc_in<bool> enable{"enable"};

    // Entradas
    sc_in<sc_int<32>> pc_in{"pc_in"};
    sc_in<sc_int<32>> mem_data_in{"mem_data_in"};
    sc_in<sc_int<32>> alu_result_in{"alu_result_in"};
    sc_in<sc_int<5>> rd_in{"rd_in"};
    sc_in<bool> regWrite_in{"regWrite_in"};
    sc_in<bool> memToReg_in{"memToReg_in"};

    // Saídas
    sc_out<sc_int<32>> pc_out{"pc_out"};
    sc_out<sc_int<32>> mem_data_out{"mem_data_out"};
    sc_out<sc_int<32>> alu_result_out{"alu_result_out"};
    sc_out<sc_int<5>> rd_out{"rd_out"};
    sc_out<bool> regWrite_out{"regWrite_out"};
    sc_out<bool> memToReg_out{"memToReg_out"};

    void process() {
        if (reset.read()) {
            pc_out.write(0);
            mem_data_out.write(0);
            alu_result_out.write(0);
            rd_out.write(0);
            regWrite_out.write(false);
            memToReg_out.write(false);
        } else if (enable.read()) {
            pc_out.write(pc_in.read());
            mem_data_out.write(mem_data_in.read());
            alu_result_out.write(alu_result_in.read());
            rd_out.write(rd_in.read());
            regWrite_out.write(regWrite_in.read());
            memToReg_out.write(memToReg_in.read());
        }
    }

    SC_CTOR(MEM_WB) {
        std::cout << "New component - MEM/WB" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif
