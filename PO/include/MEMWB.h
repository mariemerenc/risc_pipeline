#ifndef MEMWB_H
#define MEMWB_H

#include "systemc.h"

SC_MODULE(MEMWB) {
    sc_in<sc_uint<32>> mem_data_in, alu_result_in;
    sc_in<sc_uint<5>> write_reg_in;
    sc_in<bool> reg_write_in, mem_to_reg_in;

    sc_out<sc_uint<32>> mem_data_out, alu_result_out;
    sc_out<sc_uint<5>> write_reg_out;
    sc_out<bool> reg_write_out, mem_to_reg_out;

    void process() {
        mem_data_out.write(mem_data_in.read());
        alu_result_out.write(alu_result_in.read());
        write_reg_out.write(write_reg_in.read());
        reg_write_out.write(reg_write_in.read());
        mem_to_reg_out.write(mem_to_reg_in.read());
    }

    SC_CTOR(MEMWB) {
        SC_METHOD(process);
        sensitive << mem_data_in << alu_result_in << write_reg_in
                  << reg_write_in << mem_to_reg_in;
    }
};

#endif
