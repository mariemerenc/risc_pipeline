#ifndef EX_MEM_H
#define EX_MEM_H

#include <systemc.h>

SC_MODULE(EX_MEM) {
    sc_in<bool> clock{"clock"};
    sc_in<bool> reset{"reset"};
    sc_in<bool> enable{"enable"};

    // Entradas
    sc_in<sc_int<32>> pc_in{"pc_in"};
    sc_in<sc_int<32>> alu_result_in{"alu_result_in"};
    sc_in<sc_int<32>> rs2_data_in{"rs2_data_in"};  // dado para escrita na memória
    sc_in<sc_int<5>> rd_in{"rd_in"};
    sc_in<bool> memRead_in{"memRead_in"};
    sc_in<bool> memWrite_in{"memWrite_in"};
    sc_in<bool> regWrite_in{"regWrite_in"};
    sc_in<bool> memToReg_in{"memToReg_in"};

    // Saídas
    sc_out<sc_int<32>> pc_out{"pc_out"};
    sc_out<sc_int<32>> alu_result_out{"alu_result_out"};
    sc_out<sc_int<32>> rs2_data_out{"rs2_data_out"};
    sc_out<sc_int<5>> rd_out{"rd_out"};
    sc_out<bool> memRead_out{"memRead_out"};
    sc_out<bool> memWrite_out{"memWrite_out"};
    sc_out<bool> regWrite_out{"regWrite_out"};
    sc_out<bool> memToReg_out{"memToReg_out"};

    void process() {
        if (reset.read()) {
            pc_out.write(0);
            alu_result_out.write(0);
            rs2_data_out.write(0);
            rd_out.write(0);
            memRead_out.write(false);
            memWrite_out.write(false);
            regWrite_out.write(false);
            memToReg_out.write(false);
        } else if (enable.read()) {
            pc_out.write(pc_in.read());
            alu_result_out.write(alu_result_in.read());
            rs2_data_out.write(rs2_data_in.read());
            rd_out.write(rd_in.read());
            memRead_out.write(memRead_in.read());
            memWrite_out.write(memWrite_in.read());
            regWrite_out.write(regWrite_in.read());
            memToReg_out.write(memToReg_in.read());
        }
    }

    SC_CTOR(EX_MEM) {
        std::cout << "New component - EX/MEM" << std::endl;
        SC_METHOD(process);
        sensitive << clock.pos();
    }
};

#endif
