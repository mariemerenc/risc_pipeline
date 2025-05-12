#ifndef EXMEM_H
#define EXMEM_H

#include "systemc.h"

SC_MODULE(EXMEM) {
    sc_in<sc_uint<32>> alu_result_in, pc_branch_in, reg_data2_in;
    sc_in<sc_uint<5>> reg_dst_in;
    sc_in<bool> zero_in, reg_write_in, mem_read_in, mem_write_in, mem_to_reg_in, branch_in;

    sc_out<sc_uint<32>> alu_result_out, pc_branch_out, reg_data2_out;
    sc_out<sc_uint<5>> reg_dst_out;
    sc_out<bool> zero_out, reg_write_out, mem_read_out, mem_write_out, mem_to_reg_out, branch_out;

    void process() {
        alu_result_out.write(alu_result_in.read());
        pc_branch_out.write(pc_branch_in.read());
        reg_data2_out.write(reg_data2_in.read());
        reg_dst_out.write(reg_dst_in.read());
        zero_out.write(zero_in.read());
        reg_write_out.write(reg_write_in.read());
        mem_read_out.write(mem_read_in.read());
        mem_write_out.write(mem_write_in.read());
        mem_to_reg_out.write(mem_to_reg_in.read());
        branch_out.write(branch_in.read());
    }

    SC_CTOR(EXMEM) {
        SC_METHOD(process);
        sensitive << alu_result_in << pc_branch_in << reg_data2_in
                  << reg_dst_in << zero_in << reg_write_in << mem_read_in
                  << mem_write_in << mem_to_reg_in << branch_in;
    }
};

#endif
